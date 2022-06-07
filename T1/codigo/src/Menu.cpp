#include "../include/Menu.h"
#include <iomanip>
#include <chrono>
#include "iostream"
using namespace std;
typedef std::chrono::high_resolution_clock Clock;


Menu::~Menu() = default;

Menu::Menu(Application &application): application(application) {}

int Menu::readInt() {
    int option;
    while (true){
        stringstream ss;
        ss << readStr(); ss >> option;
        if(!ss.fail() && ss.eof() && option >= 0 && option <= 3) break;
        cout << "Invalid input. Try a valid number..." << endl;
    }
    cout << endl;
    return option;
}

int Menu::askUser(){
    int option;
    cout << "Which day do you wanna see? (1-20) ";
    while (true){
        stringstream ss;
        ss << readStr(); ss >> option;
        if(!ss.fail() && ss.eof() && option >= 1 && option <= 20) break;
        cout << "Invalid input. Try a valid number..." << endl;
    }
    cout << endl;
    return option;
}

std::string Menu::readStr() {
    string s, result;
    cout << ": ";
    getline(cin, s);
    for(char &c : s){
        result += toupper(c);
    }
    return result;
}

Menu *Menu::invalidInput() {
    cout << "Invalid input option!" << endl;
    return this;
}

MainMenu::MainMenu(Application &app): Menu(app){}

int Menu::getAllOrdersReward( vector<Order> orders){
    auto totalProfit = 0;
    for(const auto& order : orders){
        totalProfit += order.getReward();
    }
    return totalProfit;
}
void MainMenu::display(){

    cout << endl;
    cout << " | --------------------------------------------- |" << endl;
    cout << " | ***************** MAIN MENU ***************** |" << endl;
    cout << " | --------------------------------------------- |" << endl;
    cout << " | Execute the following:                        |" << endl;
    cout << " | --------------------------------------------- |" << endl;
    cout << " | 1 - Scenery 1                                 |" << endl;
    cout << " | 2 - Scenery 2                                 |" << endl;
    cout << " | 3 - Scenery 3                                 |" << endl;
    cout << " | --------------------------------------------- |" << endl;
    cout << " | 0 - EXIT                                      |" << endl;
    cout << " | --------------------------------------------- |" << endl;
    cout << endl;
}

Menu *MainMenu::executeMenu() {

    switch (readInt()) {
        case 1: {
            /***** RESETTING APPLICATION *****/
            application.filepath = "../../input/" + to_string(askUser()) + "/";
            application.orders.clear();
            application.trucks.clear();
            application.loadData();

            /***** EXECUTION TIME *****/
            int numOrders=0;
            auto t1 = Clock::now();
            int result = application.scenery1((int &) numOrders);
            auto t2 = Clock::now();
            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

            /***** OUTPUT *****/
            cout << "Execution Time: " << time_taken << "ns" << endl;
            cout << "Number of Trucks Used: " << result << "/" << application.trucks.size() <<
            " (" << fixed << setprecision(2) << (float)(result*100)/application.trucks.size() << "%)" << endl;
            cout << "Number of Orders Processed: " << numOrders << "/" << application.orders.size()
            << " (" << fixed << setprecision(2) << (float)(numOrders*100)/application.orders.size() << "%)" << endl;;
            return this;
        }
        case 2: {
            /***** RESETTING APPLICATION *****/
            application.filepath = "../../input/" + to_string(askUser()) + "/";
            application.orders.clear();
            application.trucks.clear();
            application.loadData();

            /***** EXECUTION TIME *****/
            auto t1 = Clock::now();
            int result = application.scenery2();
            auto t2 = Clock::now();
            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

            /***** OUTPUT *****/
            cout << "Execution Time: " << time_taken << "ns" << endl;
            cout << "Total Profit: " << result << "$" << " / " << getAllOrdersReward(application.orders) << "$" << " ("
            << fixed << setprecision(2) << (float)(result*100)/getAllOrdersReward(application.orders) << "%)" << endl;
            return this;
        }
        case 3:{
            /***** RESETTING APPLICATION *****/
            application.filepath = "../../input/" + to_string(askUser()) + "/";
            application.orders.clear();
            application.trucks.clear();
            application.loadData();

            /***** EXECUTION TIME *****/
            auto t1 = Clock::now();
            vector<Order> result = application.scenery3();
            auto t2 = Clock::now();
            auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

            /***** AVERAGE DELIVERY TIME *****/
            int averageTime = 0, averageTime2 = 0, min1, min2, time = 8 * 3600;
            vector<Order> testVec;

            for(const auto& order : result){
                averageTime += order.getDuration();
            }
            for(const Order& order : application.orders){
                if(order.getDuration() <= time) {

                    testVec.push_back(order);
                    time -= order.getDuration();
                }
                else break;
            }

            for(const auto& order : testVec){
                averageTime2 += order.getDuration();
            }

            min1 = (float)(averageTime/result.size())/60;
            min2 = (float)(averageTime2/testVec.size())/60;


            /***** OUTPUT *****/
            cout << "Execution Time: " << time_taken << "ns" << endl;
            cout << "Average Normal Delivery Time: " << min2 << "min" << endl;
            cout << "Average Express Delivery Time: " << min1 << "min" << endl;
            cout << "Express Deliveries: " << result.size() << "/" << application.orders.size()
            << " (" << fixed << setprecision(2) << (float)(result.size()*100)/application.orders.size() << "%)" << endl;
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}
