//
// Created by franc on 12/04/2022.
//

#ifndef UNTITLED_TRUCK_H
#define UNTITLED_TRUCK_H


#include "Cargo.h"

/**
 * This class represents the trucks in this project. Trucks are represented by a maximum volume, a maximum weight and cost of transportation.
 */
class Truck {
    unsigned maxVolume;
    unsigned maxWeight;
    unsigned cost;
    bool isFull;
    Cargo cargo;
public:
    /**
     * Class constructor with 3 unsigned objects
     * @param maxVolume truck's maximum supported volume
     * @param maxWeight truck's maximum supported weight
     * @param cost truck's cost of transportation
     */
    Truck(unsigned maxVolume, unsigned maxWeight, unsigned cost);

    /**
     * Class destructor to clear the object in memory
     */
    ~Truck();

    /**
     * returns truck's maximum volume supported
     * @return maxVolume parameter
     */
    unsigned getMaxVolume();

    /**
     * returns truck's maximum weight supported
     * @return maxWeight parameter
     */
    unsigned getMaxWeight();

    /**
     * returns truck's cost to cargo transport
     * @return cost parameter
     */
    unsigned getCost();

    /**
     * returns assigned value (true or false) to full parameter
     * @return assigned value
     */
    bool getFull();

    /**
     * assigns full parameter value to true
     */
    void setFull();

    /**
     * assigns full parameter value to false
     */
    void setEmpty();

    /**
     * returns truck´s cargo
     * @return truck's cargo
     */
    Cargo &getCargo();

};


#endif //DA_T1_TRUCK_H
