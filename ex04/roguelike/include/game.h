#ifndef ROGUELIKE_GAME_H_
#define ROGUELIKE_GAME_H_

#include <list>
#include <memory>

#include <SDL.h>

#include "entity.h"
#include <vector>
#include "resource_loader.h"
#include "area.h"
#include "camera.h"
#include "logic/logic.h"
#include "entities/player.h"


class Game {
    bool running = true;

	Area area;
	Logic logic;
    std::list<std::shared_ptr<Entity>> entities;

    std::unique_ptr<ResourceLoader> resource_loader;

    std::list<SDL_Event> events;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

  public:
    std::list<std::shared_ptr<Entity>> dead_entities;
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

    void spawn_enemies();

    void do_damage(int hp, std::vector<Vec2> points, Entity * damage_dealer);
    void add_projectile(Weapon w_type, std::vector<Vec2> points);
};

#endif  // ROGUELIKE_GAME_H_
