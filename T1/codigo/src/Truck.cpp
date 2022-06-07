//
// Created by franc on 12/04/2022.
//

#include "../include/Truck.h"
using namespace std;

Truck::Truck(unsigned int maxVolume, unsigned int maxWeight, unsigned int cost) :
        maxVolume(maxVolume), maxWeight(maxWeight), cost(cost), cargo(Cargo(maxVolume, maxWeight, cost, 8 * 3600)), isFull(false) {}

Truck::~Truck() = default;

unsigned int Truck::getMaxVolume() {
    return this->maxVolume;
}

unsigned int Truck::getMaxWeight() {
    return this->maxWeight;
}

unsigned int Truck::getCost() {
    return this->cost;
}

Cargo& Truck::getCargo() {
    return cargo;
}

bool Truck::getFull() {
    return this->isFull;
}

void Truck::setFull() {
    this->isFull = true;
}
void Truck::setEmpty() {
    this->isFull = false;
}