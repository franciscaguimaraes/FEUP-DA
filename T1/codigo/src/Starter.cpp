//
// Created by franc on 12/04/2022.
//

#include "../include/Starter.h"

Starter::Starter() {
    menuStack.push(new MainMenu(application));
}

void Starter::start() {
    while (!menuStack.empty()) {

        menuStack.top()->display();
        Menu *execute = menuStack.top()->executeMenu();

        if (execute){
            if (execute != menuStack.top()){
                menuStack.push(execute);
            }
        } else {
            delete menuStack.top();
            menuStack.pop();
        }
    }
}