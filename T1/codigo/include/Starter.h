//
// Created by franc on 12/04/2022.
//

#ifndef DA_T1_STARTER_H
#define DA_T1_STARTER_H

#include "Application.h"
#include "Menu.h"
#include <stack>
/**
 * This class starts our application.
 */
class Starter {
    Application application;
    std::stack<Menu*> menuStack;

public:
    /**
     * Default class constructor. Pushes the main menu to the menuStack
     */
    Starter();

    /**
     * Starts application loop
     */
    void start();
};


#endif //DA_T1_STARTER_H
