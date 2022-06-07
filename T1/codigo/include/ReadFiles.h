//
// Created by franc on 12/04/2022.
//

#ifndef DA_T1_READFILES_H
#define DA_T1_READFILES_H

#include <iostream>
#include <vector>
#include "Truck.h"
#include "Order.h"

/**
 * This class reads input files, initializing important vectors in the project.
 */
class ReadFiles {

public:
    /**
     * reads from file skipping first line
     * @param name file to be read
     * @return vector string
     */
    vector<string> fileReader(string name);

    /**
     * reads from file and stores into trucks' vector
     * @param s1 file to be read
     * @return vector trucks
     */
    vector<Truck> *getTruckFromFiles(string s1);

    /**
     * reads from input and stores into orders' vector
     * @param s1 file to be read
     * @return vector orders
     */
    vector<Order> *getOrderFromFiles(string s1);
};


#endif //DA_T1_READFILES_H
