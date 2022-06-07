//
// Created by franc on 18/05/2022.
//

#ifndef FEUP_DA2_STARTER_H
#define FEUP_DA2_STARTER_H


#include <stack>
#include "Application.h"
#include "Menu.h"
using namespace std;

/**
 * This class starts our application.
 */
class Starter {
    Application application;
    stack<Menu*> menuStack;

public:
    /**
     * Default class constructor. Pushes the main Menu to the menuStack
     */
    Starter();

    /**
     * Starts Application loop
     */
    void start();
};

#endif //FEUP_DA2_STARTER_H
