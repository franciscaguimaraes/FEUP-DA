//
// Created by franc on 18/05/2022.
//

#include "../include/Application.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

Application::Application() = default;

string getFilePath(int numInput){
    string filepath;
    if(numInput >= 10){
        filepath = "../../input/in" + to_string(numInput) + ".txt";
    } else {
        filepath = "../../input/in0" + to_string(numInput) + ".txt";
    }
    return filepath;
}

void Application::scenery1_1( int numInput){

    filepath = getFilePath(numInput);
    Graph graph = Graph::createGraph(filepath, false, 0);

    auto path = graph.path_taken(1, graph.n,-1);
    cout << endl;
    cout << "Path Taken: " << endl;
    cout << "------------------------------ " << endl << endl;

    int j = 0;
    for (auto const &i: path) {
        j++;
        if (j == path.size()) {
            cout << i;
        } else {
            cout << i << " -> ";
        }
    }
    cout << endl << endl;
    cout << "------------------------------ " << endl ;
    cout << "Path Size: " << path.size() << endl;
    cout << "Maximum Capacity: " << graph.nodes[graph.n].dist << endl << endl << endl;
}

void Application::scenery1_2(int numInput){
    filepath = getFilePath(numInput);
    Graph graph = Graph::createGraph(filepath, false, 0);

    int count = 1;
    int max = INF;

    while(true){
        auto path = graph.path_taken(1, graph.n, max);

        if(path.empty()) break;

        cout << "Option " << count++ << ":" << endl;
        cout << "------------------------------ " << endl ;
        cout << endl;
        cout << "Path Taken: " << endl;

        int j = 0;
        for (auto const &i: path) {
            j++;
            if (j == path.size()) {
                cout << i;
            } else {
                cout << i << " -> ";
            }
        }

        cout << endl << endl;
        cout << "Path Size: " << path.size() << endl;
        cout << "Maximum Capacity: " << graph.nodes[graph.n].dist << endl << endl;
        cout << "------------------------------ " << endl << endl;

        int layoverCount = path.size() - 1;
        max = layoverCount - 1;
    }
}

void Application::scenery2_1(int numInput, int size){
    int maxFlow = 0;
    filepath = getFilePath(numInput);
    Graph graph = Graph::createGraph(filepath, true, 1);

    graph.addEdge(1, 2, size, 1); // new node with limiting maxFlow capacity

    cout << "Paths Chosen For This Group: " << endl << endl ;
    cout << "------------------------------ " << endl << endl;
    graph.edmondsKarp(1, graph.n, maxFlow, 1);
    cout << "------------------------------ " << endl;
    if(maxFlow < size){
        cout << "[INPUT] Group Size : " << size << endl;
        cout << "[ERROR!] Maximum group size is " << maxFlow << " for this day" <<endl << endl << endl;
    } else{
        cout << "[INPUT] Group Size : " << size << endl;
        cout << "[FOUND] Group Size : " << maxFlow << endl << endl << endl;
    }
}

// this function implements the same code as 2.1 only size is increased by units. size += units
// void Application:: scenery2_2(int numInput, int size, int units){}

void Application:: scenery2_3( int numInput){

    cout << endl;
    int maxFlow = 0;
    filepath = getFilePath(numInput);
    Graph graph = Graph::createGraph(filepath, true, 0);

    cout << "Paths Taken: " << endl;
    cout << "------------------------------ " << endl << endl;
    graph.edmondsKarp(1, graph.n, maxFlow, 0);
    cout << "------------------------------ " << endl;
    cout << "Group Maximum Size: " << maxFlow << endl << endl << endl;
}

void Application:: scenery2_4( int numInput){

    cout << endl;
    filepath = getFilePath(numInput);
    Graph graph = Graph::createGraph(filepath, false, 0);

    graph.earliestStart();
    cout << "------------------------------ " << endl << endl;
    cout << "Meet at Location: " << graph.n <<" | Ready At: " << graph.nodes[graph.n].earliestStart << endl << endl ;
    cout << "------------------------------ " << endl << endl << endl;

}

void Application:: scenery2_5( int numInput){

    cout << endl;
    filepath = getFilePath(numInput);
    Graph graph = Graph::createGraph(filepath, false, 0);

    graph.flSolve();
}
