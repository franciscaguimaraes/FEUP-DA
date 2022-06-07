//
// Created by franc on 12/04/2022.
//

#include "../include/ReadFiles.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

vector<string> ReadFiles::fileReader(string name){
    ifstream fileName;
    string line;

    vector<string> result;
    fileName.open(name, ios::out);
    if (fileName.is_open()) {
        getline(fileName, line);
        while(getline(fileName, line)) {
            result.push_back(line);
        }
        fileName.close();
    }
    return result;
}

bool fileExists(string f_name) {
    ifstream f;
    f.open(f_name);
    if(f.is_open()) {
        f.close();
        return true;
    }
    else {
        cout << "File does not exist..." << endl;
        return false;
    }
}

vector<Truck> *ReadFiles::getTruckFromFiles(string s1) {
    vector<Truck> * trucks = new vector<Truck>;
    vector<string> result;
    if(!fileExists(s1)) return nullptr;
    result = fileReader(s1);
    for(auto line : result) {
        stringstream ss(line);
        unsigned maxVolume, maxWeight, cost;
        ss >> maxVolume;
        ss >> maxWeight;
        ss >> cost;
        trucks->push_back(Truck(maxVolume, maxWeight, cost));
    }
    return trucks;
}

vector<Order> *ReadFiles::getOrderFromFiles(string s1) {
    vector<Order> * order = new vector<Order>;
    vector<string> result;
    if(!fileExists(s1)) return nullptr;
    result = fileReader(s1);
    for(auto line : result) {
        stringstream ss(line);
        unsigned volume, weight, reward, duration;
        ss >> volume;
        ss >> weight;
        ss >> reward;
        ss >> duration;
        order->push_back(Order(volume, weight, reward, duration));
    }
    return order;
}
