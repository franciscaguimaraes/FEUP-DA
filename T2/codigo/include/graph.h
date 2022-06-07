//
// Created by franc on 17/05/2022.
//

#ifndef FEUP_DA2__GRAPH_H_
#define FEUP_DA2__GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <queue>
#define INF (INT_MAX/2)


using namespace std;
/**
 * Graph structure: composed of nodes linked by edges
 */
class Graph {
public:
    /**
     * An edge links two nodes and can have a capacity and duration
     * In this case, an edge is a connection between two locations and holds
     * the path the vehicle takes to connects them
     */
    struct Edge {
        int dest;  // Destination nodes
        int cap; // An integer weight
        int dur; // duration
    };

    /**
     * A node is a location, holding additional attributes
     */
    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        int layovers;
        int earliestStart;
        int FL = 0;
        int grau;
    };

    int n; // Graph size (vertices are numbered from 1 to n)
    bool hasResidual; // false: directed graph; true: undirected graph
    vector<Node> nodes; // The list of nodes being represented
    vector<vector <int>> residualMatrix; // residualMatrix to store residual capacities

public:

/**
     * Adds the edges read from file s1
     * @param s1 file name to be read
     * @param res if we add residual edges or not. true if we want to, false otherwise
     * @param offSet shift graph numbers one unit to add an initial node with input given capacity
     * @return graph created
     */
    static Graph createGraph(const string& s1, bool residual, int offSet);

    /**
     * Creates a graph with N nodes and if there is a direction to their edges
     * @param nodes number of nodes to be built
     * @param residual boolean if residual edge is to be existed exists
     */
    explicit Graph(int nodes, bool residual = false);

    /**
     * Adds an edge between two nodes
     * @param src start node to be linked
     * @param dest end node to be linked
     * @param capacity capacity (weight) of the edge
     * @param duration additional attribute which represents the duration of that path
     */
    void addEdge(int src, int dest, int capacity = 1, int duration = 1);

    /**
     * this function returns maximum capacity from a to b
     * @param a start node
     * @param b end node
     * @return the maximum capacity possible going from a node to b node
     */
    int maxCap(int a, int b);

    /**
     * this functions returns maximum capacity regardim maximum amout of layovers
     * @param a start node
     * @param b end node
     * @param max maximum number of layovers it can reach
     * @return the maximum capacity possible going from a node to b node regarding the maximum amount of
     * layovers, passed onto the function through the "max" parameter
     */
    int pareto(int a, int b,int max);

    /**
     * this function prints paths
     * @param a start node
     * @param b end node
     * @param max maximum number of layovers it can reach, default value is -1 which will mean the function to call
     * is the 1.1 maxCap, else it calls pareto function from 1.2
     * @return the path taken to reach the maximum capacity possible from a node to b, if a "max" parameter is
     * provided, such maximum capacity is calculated regarding a number of maximum layovers it can reach.
     */
    list<int> path_taken(int a, int b, int max);

    /**
     * Returns true if there is a path from source 's' to target 't'.
     * @param s source value
     * @param t target value
     * @return bool value
     */
    bool bfs(int s, int t);

    /**
     * Returns the maximum flow from s to t in the given graph.
     * @param s source value
     * @param t target value
     * @param maxFlow maximum flow passed by reference
     * @param offset for printing purposes only
     */
    void edmondsKarp(int s, int t, int &maxFlow, int offset);

    /**
     *  calculates through the critical path method the minimum duration of the project
     */
    void earliestStart();

    /**
     * calculates the difference between the earliest start of node and the earliest start of and edge + its duration
     */
    void flSolve();
};

#endif