//
// Created by franc on 18/05/2022.
//

#include "../include/Menu.h"
#include "iostream"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

Menu::~Menu() = default;

Menu::Menu(Application &application): application(application) {}

int Menu::askUser(){
    int option;
    cout << "Choose a day please (1-20) ";
    while (true){
        stringstream ss;
        ss << readStr(); ss >> option;
        if(!ss.fail() && ss.eof() && option >= 0 && option <=20) break;
        cout << "Invalid input file. Try a valid number..." << endl;
    }

    return option;
}

int askUserDurationFunc(){
    int option;
    cout << "Choose a day please (1-10) ";
    while (true){
        stringstream ss;
        ss << Menu::readStr(); ss >> option;
        if(!ss.fail() && ss.eof() && option >= 0 && option <=10) break;
        cout << "Invalid input file. Try a valid number..." << endl;
    }

    return option;
}

int askSize(){
    int option;
    cout << "Group Size? ";
    while (true){
        stringstream ss;
        ss << MainMenu::readStr(); ss >> option;
        if(!ss.fail() && ss.eof() && option >= 0) break;
        cout << "Invalid input size. Try a valid number..." << endl;
    }
    return option;
}

int askIncreaseUnits(){
    int option;
    cout << "Increase Group Size by ";
    while (true){
        stringstream ss;
        ss << MainMenu::readStr(); ss >> option;
        if(!ss.fail() && ss.eof() && option >= 0) break;
        cout << "Invalid input size. Try a valid number..." << endl;
    }
    return option;
}

int Menu::readInt() {
    int opt;
    while (true){
        stringstream ss;
        ss << readStr(); ss >> opt;
        if(!ss.fail() && ss.eof() && opt>=0) break;
        cout << "Invalid input. Try a valid integer..." << endl;
    }
    cout << endl;
    return opt;
}

std::string Menu::readStr() {
    string str,ret;
    cout << ": ";
    getline(cin, str);
    for(char &c : str){
        ret += toupper(c);
    }
    return ret;
}

Menu *Menu::invalidInput() {
    cout << "Invalid input option!" << endl;
    return this;
}

MainMenu::MainMenu(Application &application): Menu(application) { }

void MainMenu::display(){
    cout << endl;
    cout << " | -------------------------------------------------------------- |" << endl;
    cout << " | ************************* MAIN MENU ************************** |" << endl;
    cout << " | -------------------------------------------------------------- |" << endl;
    cout << " | Which scenery do you want to execute considering the following |" << endl;
    cout << " | group transportation requirements:                             |" << endl;
    cout << " | -------------------------------------------------------------- |" << endl;
    cout << " | 1 - Non-seperated Groups (Scenery 1)                           |" << endl;
    cout << " |                                                                |" << endl;
    cout << " | 2 - Seperated Groups (Scenery 2)                               |" << endl;
    cout << " | -------------------------------------------------------------- |" << endl;
    cout << " | 0 - EXIT                                                       |" << endl;
    cout << " | -------------------------------------------------------------- |" << endl;
    cout << endl;
}

Menu *MainMenu::executeMenu() {
    switch (readInt()) {
        case 1: return new SceneryOne(application);
        case 2: return new SceneryTwo(application);
        case 0: return nullptr;
        default: return invalidInput();
    }
}


SceneryOne::SceneryOne(Application &application) : Menu(application) { }

void SceneryOne::display() {
    cout << endl;
    cout << " | ------------------------------------------------------------- |" << endl;
    cout << " | ********************* SCENERY 1 MENU ************************ |" << endl;
    cout << " | ------------------------------------------------------------- |" << endl;
    cout << " | Chose which functionality you would like to execute:          |" << endl;
    cout << " | ------------------------------------------------------------- |" << endl;
    cout << " | 1 - Maximize group size and determine a path;                 | " << endl;
    cout << " |                                                               |" << endl;
    cout << " | 2 - Maximize group size and minimize the number of transfers. | " << endl;
    cout << " | ------------------------------------------------------------- |" << endl;
    cout << " | 0 - BACK TO MAIN MENU                                         |" << endl;
    cout << " | ------------------------------------------------------------- |" << endl;
    cout << endl;
}

Menu *SceneryOne::executeMenu() {
    switch (readInt()) {
        case 1: {
            int numInput = askUser();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery1_1(numInput);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;
            return this;
        }
        case 2: {
            int numInput = askUser();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery1_2(numInput);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

SceneryTwo::SceneryTwo(Application &application) : Menu(application) { }

void SceneryTwo::display() {
    cout << endl;
    cout << " | ------------------------------------------------------------------- |" << endl;
    cout << " | ************************* SCENERY 2 MENU ************************** |" << endl;
    cout << " | ------------------------------------------------------------------- |" << endl;
    cout << " | Chose which functionality you would like to execute:                |" << endl;
    cout << " | ------------------------------------------------------------------- |" << endl;
    cout << " | 1 - Determine a path for a group, given its size;                   |" << endl;
    cout << " |                                                                     |" << endl;
    cout << " | 2 - Correct a path so the group size can increase;                  |" << endl;
    cout << " |                                                                     |" << endl;
    cout << " | 3 - Determine the maximum group size and its path;                  |" << endl;
    cout << " |                                                                     |" << endl;
    cout << " | 4 - Determine when the group would meet again at the destination;   |" << endl;
    cout << " |                                                                     |" << endl;
    cout << " | 5 - Determine the maximum waiting time and the places where there   |" << endl;
    cout << " | would be elements that wait this time.                              |" << endl;
    cout << " | ------------------------------------------------------------------- |" << endl;
    cout << " | 0 - BACK TO MAIN MENU                                               |" << endl;
    cout << " | --------------------------------------------------------------------|" << endl;
    cout << endl;
}

Menu *SceneryTwo::executeMenu() {
    switch (readInt()) {
        case 1: {
            int numInput = askUser();
            int size = askSize();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery2_1(numInput, size);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;

            return this;
        }
        case 2: {
            int numInput = askUser();
            int size = askSize();
            int units = askIncreaseUnits();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery2_1(numInput, size + units);
            //application.scenery2_2(numInput,size, units);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;

            return this;
        }
        case 3: {
            int numInput = askUser();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery2_3(numInput);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;

            return this;
        }
        case 4: {
            int numInput = askUserDurationFunc();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery2_4(numInput);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;
            return this;
        }
        case 5: {
            int numInput = askUserDurationFunc();
            cout << endl;

            auto t1 = Clock::now();

            application.scenery2_5(numInput);

            auto t2 = Clock::now();

            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            cout << "Execution Time: " << time_taken << "ns" << endl;
            return this;
        }

        case 0: return nullptr;
        default: return invalidInput();
    }
}

