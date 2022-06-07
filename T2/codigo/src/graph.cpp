//
// Created by franc on 17/05/2022.
//
#include "../include/graph.h"
#include "../include/ReadFiles.h"
#include "../include/MaxHeap.h"
#include <iterator>
#include <iostream>
#include <vector>


using namespace std;

// Constructor: nr nodes and if it has residual Graph
Graph::Graph(int num, bool hasResidual) {
    this->n = num;
    this->hasResidual = hasResidual;
    nodes.resize(n+1); // +1 because nodes start at 1

    if(hasResidual){
        residualMatrix.resize(n+1); // capacityMatrix for residual results
        for (int i=1; i<=n; i++){
            residualMatrix[i].resize(n+1);
        }
    }
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int cap, int dur) {
    if (src < 0 || src > n || dest < 1 || dest > n) return;

    nodes[src].adj.push_back({dest, cap, dur});

    if(hasResidual){
        residualMatrix[src][dest] = cap; // indicates residual capacity of edge from i to j
        nodes[dest].adj.push_back({src,cap,dur}); // might have to go backwards to find augmenting paths
    }
}

/***** IMPORT FILE CONTENTS TO GRAPH *****/

Graph Graph::createGraph(const string& s1, bool residual, int offSet){
    string firstLine;
    int numNodes;

    fstream fileName(s1);
    getline(fileName, firstLine);
    stringstream ss(firstLine);
    ss >> numNodes;
    fileName.close();

    Graph graph = Graph(numNodes + offSet, residual); // offset to shift nodes number 1 unit to fit an initial node to limit capacity

    vector <Contents> result = fileReader(s1);
    for(auto contents : result){
        graph.addEdge(contents.scr + offSet, contents.dest + offSet, contents.cap, contents.dur);
    }

    return graph;
}

/***** SCENERY 1 FUNCTIONS *****/

int Graph::maxCap(int a, int b) {

    for (int i = 1; i <= n; i++) {
        nodes[i].pred = -1;
        nodes[i].dist = 0;
    }

    nodes[a].dist = INF;
    MaxHeap<int, int> heap(n, -1);

    for (int i = 1; i <= n; i++) {
        heap.insert(i, nodes[i].dist);
    }

    while (heap.getSize() > 0) {
        int v = heap.removeMax();
        for (auto e: nodes[v].adj) {
            if (min(nodes[v].dist, e.cap) > nodes[e.dest].dist) {
                nodes[e.dest].dist = min(nodes[v].dist, e.cap);
                nodes[e.dest].pred = v;
                heap.increaseKey(e.dest, nodes[e.dest].dist);
            }
        }
    }

    if (nodes[b].dist != 0)
        return nodes[b].dist;
    return -1;
}

int Graph::pareto(int a, int b,int max){
    for (int i = 1; i <= n; i++) {
        nodes[i].pred = -1;
        nodes[i].dist = 0;
        nodes[i].layovers = INF;
    }

    nodes[a].dist = INF;
    nodes[a].layovers = 0;
    MaxHeap<int, int> heap(n, -1);

    for (int i = 1; i <= n; i++) {
        heap.insert(i, nodes[i].dist);
    }

    while (heap.getSize() > 0) {
        int v = heap.removeMax();
        for (auto e: nodes[v].adj) {
            if (min(nodes[v].dist, e.cap) > nodes[e.dest].dist && (nodes[v].layovers + 1)<=max) {
                nodes[e.dest].dist = min(nodes[v].dist, e.cap);
                nodes[e.dest].layovers = nodes[v].layovers + 1;
                nodes[e.dest].pred = v;
                heap.increaseKey(e.dest, nodes[e.dest].dist);
            }
        }
    }

    if (nodes[b].dist != 0)
        return nodes[b].dist;
    return -1;
}

list<int> Graph::path_taken(int a, int b, int max) {
    int result;

    if(max == -1){
        result = maxCap(a, b);
    } else {
        result = pareto(a, b, max);
    }

    if(result == -1 ){
        return {};
    }

    list<int> path = {b};
    int parent = b;
    if (nodes[b].pred == -1)
        return {};
    while (parent != a) {
        parent = nodes[parent].pred;
        path.push_front(parent);
    }
    return path;
}

/***********/

/***** SCENERY 2 FUNCTIONS ****/

bool Graph::bfs(int s, int t) {

    for (int i=1; i<=n; i++){
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }

    nodes[s].visited=true;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto edge : nodes[current].adj) {
            if (!nodes[edge.dest].visited && residualMatrix[current][edge.dest] > 0) {

                if(edge.dest == t){
                    nodes[edge.dest].pred = current;
                    return true;
                }
                q.push(edge.dest);
                nodes[edge.dest].pred = current;
                nodes[edge.dest].visited = true;
            }
        }
    }

    return false;
}

void Graph::edmondsKarp(int s, int t, int &maxFlow, int offset) {

    while (bfs(s,t)) {
        int newFlow = INT_MAX;

        int cur = t;
        while (cur != s) {
            int prev = nodes[cur].pred;

            newFlow = min(newFlow, residualMatrix[prev][cur]);
            cur = prev;
        }

        cout << t - offset;
        int current = t;
        while (current != s) {
            int previous = nodes[current].pred;

            residualMatrix[previous][current] -= newFlow;
            residualMatrix[current][previous] += newFlow;
            current = previous;

            cout << " -> " << current - offset;
        }
        cout << " | " << "Branch Flow = " << newFlow;
        cout << endl << endl;

        maxFlow += newFlow;
    }
}

void Graph::earliestStart() {

    queue<int> q;

    for(int v = 1; v <= n; v++) {
        nodes[v].pred = -1;
        nodes[v].grau = 0;
        nodes[v].earliestStart = 0;
    }

    for(int v = 1; v <= n; v++) {
        for (auto w: nodes[v].adj) {
            nodes[w.dest].grau ++;
        }
    }

    for(int v = 1; v <= n; v++){
        if(nodes[v].grau == 0){
            q.push(v);
        }
    }

    int durMin = -1, vf = -1;

    while(!q.empty()){

        int v = q.front();
        q.pop();

        if (durMin < nodes[v].earliestStart){
            durMin = nodes[v].earliestStart;
            vf = v;
        }

        for (Edge &w: nodes[v].adj) {

            if (nodes[w.dest].earliestStart < nodes[v].earliestStart + w.dur) {
                nodes[w.dest].earliestStart = nodes[v].earliestStart + w.dur;
                nodes[w.dest].pred = v;
            }

            nodes[w.dest].grau--;

            if (nodes[w.dest].grau == 0) {
                q.push(w.dest);
            }
        }
    }
}

void Graph::flSolve(){
    earliestStart();
    int max = 0;

    for(int i=1; i<=n; i++) {
        for (auto e: nodes[i].adj) {
            if((nodes[e.dest].earliestStart - (nodes[i].earliestStart + e.dur)) > nodes[e.dest].FL)
                nodes[e.dest].FL = nodes[e.dest].earliestStart - (nodes[i].earliestStart + e.dur);
        }
    }

    for(int i=1; i<=n; i++){
        if(nodes[i].FL > max) {
            max = nodes[i].FL;
        }
    }

    cout << "------------------------------ " << endl << endl;


    for(int i=1; i<=n; i++){
        if(nodes[i].FL == max){
            cout << "Max Waiting Time: " << max << " | At Node: " << i << endl << endl;
            cout << "------------------------------ " << endl << endl;

            for (auto e: nodes[i].adj) {
                cout << "Max Waiting Time: " << max << " | At Edge: " << e.dest << endl << endl;
            }
        }

    }
    cout << "------------------------------ " << endl << endl << endl;
    cout << endl;

}

/**********/
