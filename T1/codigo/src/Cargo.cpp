//
// Created by franc on 12/04/2022.
//

#include "../include/Cargo.h"

Cargo::Cargo(unsigned int maxVolume, unsigned int maxWeight, unsigned int cost, unsigned int time) {
    this->maxVolume = maxVolume;
    this->maxWeight = maxWeight;
    this-> maxTime = time;
    currentVolume = 0;
    currentWeight = 0;
    currentTime = 0;
    profit = 0;
}

unsigned Cargo::getMaxVolume() const {
    return maxVolume;
}

unsigned Cargo::getCurrentVolume() const {
    return currentVolume;
}

unsigned Cargo::getMaxWeight() const {
    return maxWeight;
}

unsigned Cargo::getMaxTime() const {
    return maxTime;
}

unsigned Cargo::getCurrentWeight() const {
    return currentWeight;
}

unsigned Cargo::getCurrentTime() const {
    return currentTime;
}

int Cargo::getProfit() const {
    return profit;
}

void Cargo::setCurrentVolume(unsigned int volume) {
    currentVolume += volume;
}

void Cargo::setCurrentWeight(unsigned int weight) {
    currentWeight += weight;
}

void Cargo::setCurrentTime(unsigned int time) {
    currentTime += time;
}

void Cargo::setProfit(int value) {
    profit += value;
}

void Cargo::pushOrders(Order *order) {
    Order aux = {order->getVolume(),order->getWeight(),order->getReward(),order->getDuration()};
    getOrders().push_back(aux);
    order->setAssignedValue(true);
    setCurrentVolume(order->getVolume());
    setCurrentWeight(order->getWeight());
    setCurrentTime(order->getDuration());
}

vector<Order>& Cargo::getOrders() {
    return orders;
}

bool Cargo::canFit(const Order* package1) const {
    return ( ((maxVolume - currentVolume) >= package1->getVolume()) && ((maxWeight - currentWeight) >= package1->getWeight())
    && ((maxTime - currentTime) >= package1->getDuration()) && !package1->getAssignedValue() );
}



