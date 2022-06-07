//
// Created by franc on 12/04/2022.
//

#include "../include/Order.h"
using namespace std;

Order::Order(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int duration) :
    volume(volume), weight(weight), reward(reward), duration(duration){}

Order::~Order() = default;

unsigned int Order::getVolume() const {
    return this->volume;
}

unsigned int Order::getWeight() const {
    return this->weight;
}

unsigned int Order::getReward() const {
    return this->reward;
}

unsigned int Order::getDuration() const {
    return this->duration;
}

bool Order::getAssignedValue() const {
    return assigned;
}

void Order::setAssignedValue(bool value) {
    assigned = value;
}




