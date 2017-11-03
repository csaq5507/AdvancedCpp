#ifndef ROGUELIKE_GAME_H_
#define ROGUELIKE_GAME_H_

#include <list>
#include <memory>

#include <SDL.h>

#include "entity.h"
#include "resource_loader.h"

class Game {
    bool running = true;

    std::list<std::shared_ptr<Entity>> entities;

    std::unique_ptr<ResourceLoader> resource_loader;

    std::list<SDL_Event> events;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

  public:
    Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    // Logic / Entity Initialization

    void init();

    // -- Main Game Loop

    bool isRunning() const {
        return running;
    }

    void addEvent(SDL_Event e);

    void clearEvents();

    void updateEntities();

    void renderFrame();

    // -- Getter / Setter

    ResourceLoader& getResourceLoader() {
        return *resource_loader;
    }

    const std::list<SDL_Event>& getEvents() const {
        return events;
    }
};

#endif  // ROGUELIKE_GAME_H_
