//
// Created by franc on 12/04/2022.
//

#ifndef DA_T1_CARGO_H
#define DA_T1_CARGO_H

#include "Order.h"
#include <vector>
using namespace std;


/**
 * This class represents what each Truck is carrying (cargo)
 */

class Cargo {
    unsigned maxVolume;
    unsigned currentVolume;
    unsigned maxWeight;
    unsigned maxTime;
    unsigned currentWeight;
    unsigned currentTime;
    vector <Order> orders;
    int profit;

public:
    /**
     * Class constructor with 4 unsigned objects
     * @param maxVolume maximum supported volume
     * @param maxWeight maximum supported weight
     * @param cost ost of transportation
     * @param time company's working hours
     */
    Cargo(unsigned maxVolume, unsigned maxWeight, unsigned cost, unsigned time);

    /**
     * returns maximum volume supported
     * @return maxVolume parameter
     */
    unsigned getMaxVolume() const;

    /**
     * returns current volume
     * @return current volume
     */
    unsigned getCurrentVolume() const;

    /**
     * returns maximum weight supported
     * @return maxWeight parameter
     */
    unsigned getMaxWeight() const;

    /**
     * returns current weight
     * @return current weight
     */
    unsigned getCurrentWeight() const;

    /**
     * returns cargo profit
     * @return cargo profit
     */
    int getProfit() const;

    /**
     * updates current volume
     * @param volume value to update volume with
     */
    void setCurrentVolume(unsigned volume);

    /**
     * updates current weight
     * @param weight value to update weight with
     */
    void setCurrentWeight(unsigned weight);

    /**
     * updates current profit
     * @param value value to update profit with
     */
    void setProfit(int value);

    /**
     * returns true or false if order can fit in truck's cargo
     * @param Order pointer to order
     * @return true or false
     */
    bool canFit(const Order* Order) const;

    /**
     * adds an order to the current orders' vector updating each parameter along the way
     * @param orders pointer to orders
     */
    void pushOrders(Order* orders);

    /**
     * returns orders' vector
     * @return orders vector
     */
    vector<Order>& getOrders();

    /**
     * returns current duration of orders in cargo
     * @return time of current cargo
     */
    unsigned int getCurrentTime() const;

    /**
     * updates the current duration of orders in cargo
     * @param time updates cargo time
     */
    void setCurrentTime (unsigned int time);

    /**
     * returns maximum time of cargo
     * @return maximum time
     */
    unsigned int getMaxTime() const;
};


#endif //DA_T1_CARGO_H
