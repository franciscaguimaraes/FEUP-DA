//
// Created by franc on 12/04/2022.
//

#ifndef DA_T1_APPLICATION_H
#define DA_T1_APPLICATION_H


#include "ReadFiles.h"
#include "Cargo.h"
#include "map"


/**
 * This class represents our application and every operation being processed in the sceneries, the main focus of our project.
 */
class Application {

private:
    ReadFiles readFiles;

public:
    string filepath = "../../input/";
    vector<Truck> trucks;
    vector<Order> orders;
    vector<Cargo> cargo;

    /**
     * Default Constructor
     */
    Application();

    /**
     * Loads to the Application input files storing the data in its' respective vectors
     */
    void loadData();

    /**
     * Sorts trucks accordingly to profit importance, if we want to sort according to cost (taking profit into consideration) we follow the following equation:
     * (maxVolume^2 + maxWeight^2)*1.5+ cost;
     * If we want to sort trucks not according to profit, we sort them descending with the following equation:
     * sqrt(maxVolume^2 + maxWeight^2)
     * @param profit defines sorting order
     */
    void sortTrucks(bool profit);

    /**
     * Sorts orders ascending according to the following equation:
     * sqrt(Volume^2 + Weight^2)
     */
    void sortOrders();

    /**
     * returns the best possible order at that moment with the given percentages
     * @param v volume percentage
     * @param w weight percentage
     * @param t time percentage
     * @return pointer to the best possible order
     */
    Order *bestPossibleOrder(float v, float w, float t);

    /**
     * returns the best fit at that moment using the best possible order function and if it can fit or not in the cargo
     * @param canFit returns whether the order can fit in the cargo through reference
     * @param current pointer to the current cargo
     * @return pointer to the best possible order that fits
     */
    Order *bestFit(bool &canFit, Cargo &current);

    /**
     * @return True if all orders and all trucks have been processed. Returns false otherwise
     */
    bool isAllAssigned();

    /**
     * minimizes the number of trucks assigned for the maximum amount of orders possible
     * @param numOrders variable passed by reference, the number of orders processed
     * @return number of trucks assigned
     */
    int scenery1(int &numOrders);

    /**
     * maximizes the overall profit upon delivery
     * @return maximum profit
     */
    int scenery2();

    /**
     * Sorts orders' vector by duration and returns all orders that can be processed in a time limit of 8 hours
     * @return vector with all the orders that meet the time requirements
     */
    vector<Order> scenery3();
};

#endif //DA_T1_APPLICATION_H
