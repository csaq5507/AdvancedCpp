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
#include "sprite_set.h"
#include "utils/chrono_timer.h"

class Game {

    bool running = true;
    bool game_over_bool = false;
    std::shared_ptr<SpriteSet> game_over_sprite;

    std::list<std::shared_ptr<Entity>> entities;

    std::unique_ptr<ResourceLoader> resource_loader;

    std::list<SDL_Event> events;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
	Area area;
    int wave;

  public:
	static ChronoTimer timer;
	Logic logic;
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
    void add_projectile(std::vector<std::shared_ptr<Entity> > projectiles);
    void game_over();
};

#endif  // ROGUELIKE_GAME_H_
