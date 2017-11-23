//
// Created by daniel on 23/11/17.
//

#ifndef ADVANCEDCPP_MENU_ITEM_H
#define ADVANCEDCPP_MENU_ITEM_H


#include <SDL.h>

class MenuItem {
public:
    std::string name;
    SDL_Color color;
    bool selectable;
    bool read_only;

    MenuItem(std::string name, SDL_Color color, bool selectable, bool read_only) {
        this->name = name;
        this->color = color;
        this->selectable = selectable;
        this->read_only = read_only;
    }

    void changeName(std::string name) {
        this->name = name;
    }
};

#endif //ADVANCEDCPP_MENU_ITEM_H
