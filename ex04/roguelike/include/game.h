#ifndef ROGUELIKE_GAME_H_
#define ROGUELIKE_GAME_H_

#include <list>
#include <memory>
#include <string>
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
    bool menuOpen = true;
    bool pause = false;
    bool saveMenu = false;
    bool loadMenu = false;
    unsigned menuSelector = 0;
    std::string filename;
    std::vector<std::string> menuItems;
    SDL_Color White = {255, 255, 255};
    SDL_Color Blue = {0, 0, 255};
    SDL_Color Red = {255, 0, 0};
    SDL_Color Gray = {128, 128, 128};

    std::shared_ptr<SpriteSet> game_over_sprite;
	std::unique_ptr<ResourceLoader> resource_loader;
    std::list<SDL_Event> events;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

	//Following must be serializeable/deserializable
	bool game_over_bool = false;
	std::string current_area;
	Area area;
    int wave;
	//invariant is that the first element is the player
	//we need to change that, the whole structor is still messy
	std::list<std::shared_ptr<Entity>> entities;

  public:
	//timer must be serializeable/deserializable
	static ChronoTimer timer;
	Logic logic;

    std::list<std::shared_ptr<Entity>> dead_entities;
    Game();
	bool saveState(std::string filename);
	void loadState(std::string filename);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    // Logic / Entity Initialization

    void init();

    void clearGame();

    // -- Main Game Loop

    bool isRunning() const {
        return running;
    }

	void mainLoop();

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
    void renderMainMenu();
    void renderSaveMenu();
    void renderLoadMenu();
    void getFileNameInput(SDL_Event e);
};

#endif  // ROGUELIKE_GAME_H_
