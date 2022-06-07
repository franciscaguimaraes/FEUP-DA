//
// Created by franc on 12/04/2022.
//

#ifndef DA_T1_MENU_H
#define DA_T1_MENU_H


#include "Application.h"
#include <string>

/**
 * This class represents what is being displayed in the terminal, our menu.
 */
class Menu {
protected:
    Application &application;
public:
    /**
     * Class constructor with an application object
     * @param application application object passed by reference
     */
    explicit Menu(Application &application);

    /**
     * Class destructor to clear the object in memory
     */
    virtual ~Menu();

    /**
     * Displays the menu in the terminal
     */
    virtual void display()=0;

    /**
     * Gets a menu pointer to the next menu after this one
     * @return menu pointer
     */
    virtual Menu *executeMenu()=0;

    /**
     * Reads an integer number input from the terminal
     * @return integer number read
     */
    static int readInt();

    /**
     * Reads an integer number input from the terminal. Used to choose which data to analyse
     * @return integer number read
     */
    static int askUser();

    /**
     * Reads a string input from the terminal
     * @return string read
     */
    static std::string readStr();

    /**
    * Waits for enter key to be pressed
    */
    Menu *invalidInput();

    /**
     * returns the sum of all orders' reward
     * @param orders vector to get reward parameter
     * @return the sum
     */
    int getAllOrdersReward(vector<Order> orders);


};

class MainMenu: public Menu{
public:
    explicit MainMenu(Application &application);
    void display() override;
    Menu *executeMenu() override;
};


#endif //DA_T1_MENU_H
