//
// Created by franc on 18/05/2022.
//

#ifndef FEUP_DA2_APPLICATION_H
#define FEUP_DA2_APPLICATION_H

#include "ReadFiles.h"
#include "graph.h"
/**
 * This class represents our application and every operation being processed in the sceneries, the main focus of our project.
 */
class Application {

    public:
    string filepath;

    /**
     * Default Constructor
     */
    Application();

    /**
     * prints the maximum capacity path disregarding any other constraints
     * @param numInput File number to be processed;
     */
    void scenery1_1(int numInput);

    /**
     * prints the pareto-optimal results regarding max capacity and lowest number of layovers
     * @param numInput File number to be processed;
     */
    void scenery1_2(int numInput);

    /**
     * returns maxFlow and prints augmenting paths, taking in consideration size input
     * @param numInput file number to be processed
     * @param size input size to be considered in fordFulkerson function
     */
    void scenery2_1(int numInput, int size);

    // No need for this func as it is the same as scenery2_1
    // void scenery2_2(int numInput, int size, int units);

    /**
     * returns maxFlow and prints augmenting paths
     * @param numInput file number to be processed
     */
    void scenery2_3(int numInput);

    /**
     * returns durMin and prints the final node where the group meets again
     * @param numInput file number to be processed
     */
    void scenery2_4(int numInput);

    /**
     * returns maximum waiting time and prints it
     * @param numInput file number to be processed
     */
    void scenery2_5(int numInput);

};


#endif //FEUP_DA2_APPLICATION_H
