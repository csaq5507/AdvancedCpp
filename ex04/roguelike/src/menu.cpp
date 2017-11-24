//
// Created by daniel on 23/11/17.
//

#include <menu.h>
#include "SDL_ttf.h"
#include <boost/filesystem.hpp>
#include <string>

#ifdef WIN32
Menu::Menu() : path_to_save("%appdata%/local/roguelike/")
{
    boost::filesystem::path rootPath (path_to_save);
    boost::system::error_code returnedError;

    boost::filesystem::create_directories( rootPath, returnedError );
}
#else

Menu::Menu() : path_to_save(std::string(getenv("HOME"))+"/.roguelike/")
{
    boost::filesystem::path rootPath (path_to_save);
    boost::system::error_code returnedError;

    boost::filesystem::create_directories( rootPath, returnedError );
}

#endif

void Menu::addElement(MenuItem menu_item) {
    menu_items.push_back(menu_item);
}

void Menu::render() {
    SDL_RenderClear(renderer);
    TTF_Font* Sans = TTF_OpenFont("resources/fonts/sunvalley.ttf", 112); //this opens a font style and sets a size
    SDL_Surface* SurfaceMessage;
    SDL_Texture* Message;
    SDL_Rect Message_rect;
    for (int i = 0; i < menu_items.size(); i++) {
        if (this->actual_element == i)
            SurfaceMessage = TTF_RenderText_Solid(Sans, menu_items.at(i).name.c_str(), Red);
        else
            SurfaceMessage = TTF_RenderText_Solid(Sans, menu_items.at(i).name.c_str(), menu_items.at(i).color);
        Message = SDL_CreateTextureFromSurface(renderer, SurfaceMessage);
        Message_rect.x = 200;
        Message_rect.y = 100 + i * 150;
        Message_rect.w = 30 * menu_items.at(i).name.size();
        Message_rect.h = 100;
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    }
    SDL_RenderPresent(renderer);
}

void Menu::moveUp() {
    if (actual_element >= 0) {
        unsigned new_position = actual_element;
        while (new_position > 0) {
            new_position--;
            if (menu_items.at(new_position).selectable)
                break;
        }
        if (menu_items.at(new_position).selectable) {
            actual_element = new_position;
        }
    }
}

void Menu::moveDown() {
    if (actual_element >= 0) {
        unsigned new_position = actual_element;
        while (new_position < menu_items.size() - 1) {
            new_position++;
            if (menu_items.at(new_position).selectable)
                break;
        }
        if (menu_items.at(new_position).selectable) {
            actual_element = new_position;
        }
    }
}

std::string Menu::selectActualElement() {
    return menu_items[actual_element].name;
}

void Menu::activateAllItems() {
    for(unsigned i = 0; i < menu_items.size(); i++) {
        menu_items.at(i).selectable = true;
        menu_items.at(i).color = Blue;
    }
}

