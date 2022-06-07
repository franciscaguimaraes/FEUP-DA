//
// Created by franc on 12/04/2022.
//

#include "../include/Application.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


Application::Application() = default;

/***** FILE STUFF *****/

void Application::loadData(){
    for(const Truck& truck : *readFiles.getTruckFromFiles(filepath + "trucks.txt")){
        trucks.push_back(truck);

    }
    for(const Order& order : *readFiles.getOrderFromFiles(filepath + "orders.txt")){
        orders.push_back(order);
    }
    sortTrucks(false);
    sortOrders();
}


/***** FUNC AUX SORT TRUCKS AND ORDERS *****/

bool comparatorTruck ( Truck& i1, Truck& i2) {
    long weight_v1, weight_v2;
    weight_v1 = sqrt(pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2));
    weight_v2 = sqrt(pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2));
    return weight_v1 > weight_v2;
}
bool profitComparatorTruck(Truck& i1, Truck& i2) {
    long weight_v1, weight_v2;
    weight_v1 = (pow(i1.getMaxVolume(), 2) + pow(i1.getMaxWeight(), 2))*1.5+ i1.getCost();
    weight_v2 = (pow(i2.getMaxVolume(), 2) + pow(i2.getMaxWeight(), 2))*1.5+ i2.getCost();
    return weight_v1 > weight_v2;
}

void Application::sortTrucks(bool profit) {
    if(!profit)
        sort(trucks.begin(), trucks.end(), &comparatorTruck);
    else
        sort(trucks.begin(), trucks.end(), &profitComparatorTruck);
}

bool comparatorOrder( Order& i1, Order& i2) {
    long weight_v1, weight_v2;
    weight_v1 = sqrt(pow(i1.getVolume(), 2) + pow(i1.getWeight(), 2));
    weight_v2 = sqrt(pow(i2.getVolume(), 2) + pow(i2.getWeight(), 2));
    return weight_v1 < weight_v2;
}

void Application::sortOrders() {
        sort(orders.begin(), orders.end(), &comparatorOrder);
}


/**************FUNC AUX GREEDY ALGORITHM*****************/

Order* Application::bestPossibleOrder(float v = 1, float w = 1, float t = 1) {

    Order *min = &orders[0];
    for (Order &aOrder: orders) {
        if (!aOrder.getAssignedValue()) {
            min = &aOrder;
            break;
        }
    }

    for (Order &aOrder: orders) {
        float volumeAndWeight = (pow(aOrder.getVolume() * pow(v, 3), 2) + pow(pow(w, 3) * aOrder.getWeight(), 2));
        float duration = aOrder.getDuration() * t * 0.6;
        float bfoVolumeAndWeight = (pow(min->getVolume() * pow(v, 3), 2) + pow(pow(w, 3) * min->getWeight(), 2));
        float bfoDuration = min->getDuration() * t * 0.6;
        bool assignedValue = aOrder.getAssignedValue();

        if ((volumeAndWeight * 2 + duration) < (bfoVolumeAndWeight * 2 + bfoDuration) &&
            !assignedValue) {
            min = &aOrder;
        }
    }

    return min;
}

Order* Application::bestFit(bool &canFit, Cargo &current){
    float v = 1 - (((float)current.getMaxVolume()-(float)current.getCurrentVolume())/(float)current.getMaxVolume());
    float w = 1 - (((float)current.getMaxWeight()-(float)current.getCurrentWeight())/(float)current.getMaxWeight());
    float t = 1 - (((float)current.getMaxTime()-(float)current.getCurrentTime())/(float)current.getMaxTime());
    Order* min = bestPossibleOrder(v, w, t);

    canFit = current.canFit(min);

    if(!canFit) {
        for (Order &aOrder: orders) {
            canFit = current.canFit(&aOrder);
            if (canFit) {
                min = &aOrder;
                break;
            }
        }
    }
    return min;
}

bool Application::isAllAssigned(){
    bool flag1 = true, flag2 = true;

    for(const Order& order : orders){
        if(!order.getAssignedValue()){
            flag1 = false;
            break;
        }
    }
    for(Truck truck : trucks){
        if(!truck.getFull()){
            flag2 = false;
            break;
        }
    }
    return flag1 || flag2;
}


/******* CENÁRIO 1 *******/

int Application::scenery1(int &numOrders) {

    int numTrucks = 0;

    for (Order &aOrder: orders) {
        aOrder.setAssignedValue(false);
    }

    for (Truck &truck: trucks) {
        bool canFit = true;
        numTrucks++;
        Cargo *current = &truck.getCargo();

        Order *order = bestPossibleOrder(1, 1, 1);

        if (current->canFit(order)) {
            current->pushOrders(order);
            numOrders++;
        }
        else{
            order = bestFit(canFit, *current);
            if(canFit){
                current->pushOrders(order);
                numOrders++;
            }
        }

        do {
            order = bestFit(canFit, *current);

            if(!canFit){
                truck.setFull();
            }

            if (canFit){
                current->pushOrders(order);
                numOrders++;
            }

        } while (canFit);

        if(isAllAssigned()){
            break;
        }
    }

    return numTrucks;
}

/******* CENÁRIO 2 *******/

int Application::scenery2() {

    sortTrucks(true);
    int profitTotal = 0;

    for (Order &aOrder: orders) {
        aOrder.setAssignedValue(false);
    }

    for (Truck &truck: trucks) {
        Cargo *current = &truck.getCargo();
        bool canFit = true;

        current->setProfit(-truck.getCost());
        Order *order = bestPossibleOrder(1, 1, 1);

        if (current->canFit(order)) {
            current->pushOrders(order);
            current->setProfit(order->getReward());
        } else {
            order = bestFit(canFit, *current);
            if (canFit) {
                current->pushOrders(order);
                current->setProfit(order->getReward());
            }
        }

        do {
            order = bestFit(canFit, *current);

            if (!canFit) {
                truck.setFull();
            } else if (canFit) {
                current->pushOrders(order);
                current->setProfit(order->getReward());
            }
        } while (canFit);

        if (current->getProfit() < 0 ) {
            cargo.clear();
            truck.setEmpty();
        } else {
            profitTotal += current->getProfit();
        }

        if(isAllAssigned()){
            break;
        }
    }

    return profitTotal;

}

/******* CENÁRIO 3 ******/

vector <Order> Application::scenery3(){
    int time = 8 * 3600; // 8hrs

    vector <Order> aux(orders.begin(), orders.end());
    vector <Order> expressOrders;

    auto sorter = [](Order& i1, Order& i2){ return i1.getDuration() < i2.getDuration(); };
    sort(aux.begin(), aux.end(), sorter);

    for(const Order& order : aux){
        if(order.getDuration() <= time) {

            expressOrders.push_back(order);
            time -= order.getDuration();
        }
        else break;
    }

    return expressOrders;
}
