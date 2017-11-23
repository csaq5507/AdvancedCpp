//
// Created by danie on 23/11/17.
//

#ifndef ADVANCEDCPP_MENU_H
#define ADVANCEDCPP_MENU_H

#include <vector>
#include <string>
#include <algorithm>
#include <functional>

#include "menu_item.h"

class Menu {
public:
    std::string name;
    std::vector<MenuItem> menu_items;
    int actual_element = 0;
    SDL_Renderer* renderer = nullptr;
    SDL_Color Red = {255, 0, 0};
    SDL_Color Blue = {0, 0, 255};

    void addElement(MenuItem menu_item);
    void render();
    void moveUp();
    void moveDown();
    std::string selectActualElement();
    void activateAllItems();

};

#endif //ADVANCEDCPP_MENU_H
