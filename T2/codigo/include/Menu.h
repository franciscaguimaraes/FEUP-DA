//
// Created by franc on 18/05/2022.
//

#ifndef FEUP_DA2_MENU_H
#define FEUP_DA2_MENU_H


#include <string>
#include "Application.h"
using namespace std;

/**
 * This class represents what is being displayed in the terminal, our menu.
 */
class Menu {
protected:
    Application &application;
public:
    /**
     * Class constructor with an Application object
     * @param application Application object passed by reference
     */
    explicit Menu(Application &application);

    /**
     * Class destructor to clear the object in memory
     */
    virtual ~Menu();

    /**
     * Displays the Menu in the terminal
     */
    virtual void display()=0;

    /**
     * Gets a Menu pointer to the next Menu after this one
     * @return Menu pointer
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
    static string readStr();

    /**
    * Waits for enter key to be pressed
    */
    Menu *invalidInput();
};

class MainMenu: public Menu{
public:
    explicit MainMenu(Application &application);
    void display() override;
    Menu *executeMenu() override;
};

class SceneryOne: public Menu{
public:
    explicit SceneryOne(Application &app);
    void display() override;
    Menu *executeMenu() override;
};

class SceneryTwo: public Menu{
public:
    explicit SceneryTwo(Application &app);
    void display() override;
    Menu *executeMenu() override;
};



#endif //FEUP_DA2_MENU_H
