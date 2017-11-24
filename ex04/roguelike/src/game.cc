#include "game.h"
#include <iostream>
#include <fstream>
#include "utils/logging.h"
#include "utils/random.h"
#include "entities/projectile.h"
#include <math.h>
#include <SDL_ttf.h>
#include "sound.h"

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

ChronoTimer Game::timer{ "Game time" };
Game::Game() {
	
    window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (!window) {
        FATAL("Could not create window: %s", SDL_GetError());
    }

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        FATAL("Could not create renderer: %s", SDL_GetError());
    }

    // default background color
    SDL_SetRenderDrawColor(renderer, 0xD4, 0xC8, 0x38, 0xFF);


    resource_loader = std::make_unique<ResourceLoader>(renderer);

    wave = 1;
    game_over_sprite = resource_loader->loadSpriteSet("gameover.png");

    sounds::getInstance().play_music();


    filename = "";

    /* Initialize the default elements for the different menus*/
    main_menu.name = "Main menu";
    main_menu.addElement(*new MenuItem("Start New Game", Blue, true, true));;
    main_menu.addElement(*new MenuItem("Resume", Gray, false, true));;
    main_menu.addElement(*new MenuItem("Load Game", Blue, true, true));;
    main_menu.addElement(*new MenuItem("Save Game", Gray, false, true));;
    main_menu.addElement(*new MenuItem("Settings", Blue, true, true));;
    main_menu.addElement(*new MenuItem("Exit", Blue, true, true));
    main_menu.renderer = renderer;
    main_menu.actual_element = 0;

    save_menu.name = "Save menu";
    save_menu.addElement(*new MenuItem("Enter a filename", Blue, false, true));
    save_menu.addElement(*new MenuItem(filename, Blue, false, false));
    save_menu.renderer = renderer;
    save_menu.actual_element = -1; // No element selected
    settings_menu.name="Settings";
    settings_menu.addElement(*new MenuItem("Enable/Disable Music",Blue,true,true));
    settings_menu.addElement(*new MenuItem("Enable/Disable Sound",Blue,true,true));
    settings_menu.renderer=renderer;
    settings_menu.actual_element=0;
    load_menu.name = "Load menu";
    load_menu.addElement(*new MenuItem("Select a game to be load", Blue, false, true));
    load_menu.renderer = renderer;
    load_menu.actual_element = -1; // No element selected

    /* Add the main menu to the top of the stack to start the game with the main menu opened */
    menu_stack.push_back(main_menu);


    INFO("Game initialization done.");
}

Game::~Game() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Game::init() {
	//Load map
	current_area = "1.area";
	area.load(*resource_loader, current_area);
	//load logic map
	logic.load(area);
    entities.push_back(std::make_shared<Player>(*this, Vec2{5, 5}));
	auto player = entities.front();
	Camera::CameraControl.mode = TARGET_MODE_CENTER;
	Camera::CameraControl.SetTarget(player);
    spawn_enemies();


}

void Game::clearGame() {
    wave = 0;
    entities.clear();
}

void Game::mainLoop() {
    clearEvents();

    SDL_Event e;
    while (SDL_PollEvent(&e)) {

        addEvent(e);
    }

    if (menu_stack.size() == 0) {
        updateEntities();
        renderFrame();
   } else {
        menu_stack.back().render();
    }
}

void Game::addEvent(SDL_Event e) {
    if (e.type == SDL_QUIT) {          // The game is closed
        running = false;
        INFO("Received 'quit' signal.");
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {       // The menu is opened and the game paused
        menu_stack.push_back(main_menu);
        return;
    } else if (menu_stack.size() != 0) {           // There is no menu open
        if (menu_stack.back().name == "Save menu") {
            getFileNameInput(e);                    // Get input file name
        } else if (e.type == SDL_KEYDOWN) {         // A key was pressed
            if (e.key.keysym.sym == SDLK_ESCAPE &&
                menu_stack.back().name != "Main menu") { // Close the menu current menu
                menu_stack.pop_back();
            } else if (e.key.keysym.sym == SDLK_DOWN) {     // Go down at menu
                menu_stack.back().moveDown();
            } else if (e.key.keysym.sym == SDLK_UP) {       // GO up at menu
                menu_stack.back().moveUp();
            } else if (e.key.keysym.sym == SDLK_RETURN) {               // A menu item is selected
                auto action = menu_stack.back().selectActualElement();
                if (menu_stack.back().name == "Main menu") {
                    if (action == "Start New Game") {
                        clearGame();
                        init();
                        menu_stack.clear();
                        main_menu.activateAllItems();
                    } else if (action == "Resume") {
                        menu_stack.clear();
                    } else if (action == "Load Game") {
                        setLoadMenuItems(menu_stack.back().path_to_save);
                        menu_stack.push_back(load_menu);
                    } else if (action == "Save Game") {
                        menu_stack.push_back(save_menu);
                    } else if (action == "Settings") {
                        menu_stack.push_back(settings_menu);
                    } else if (action == "Exit") {
                        running = false;
                        INFO("Received 'quit' signal.");
                    }
                } else if (menu_stack.back().name == "Load menu") {
                    // ToDo load seceted file
                    // and start game
                    loadState(menu_stack.back().path_to_save + action);
                    menu_stack.clear();
                } else if (menu_stack.back().name == "Settings") {
                    if(action=="Enable/Disable Music"){
                        sounds::getInstance().toggle_music();
                    } else
                    {
                        sounds::getInstance().toggle_sound();

                    }
                }
            }
        }
    }

    events.push_back(std::move(e));     // Default key handling
}

void Game::clearEvents() {
    events.clear();
}

void Game::updateEntities() {
    for (auto& entity : entities) {
        entity->update();
        if(entity->is_dead()) dead_entities.push_back(entity);
    }

    for(auto &ent : dead_entities) {
        entities.remove(ent);
    }
    if(entities.size()==1)
        spawn_enemies();
}
void renderGameOver(SDL_Renderer* renderer, std::shared_ptr<SpriteSet> game_over_sprite) {
	SDL_Rect dst;
	SDL_QueryTexture(game_over_sprite->getTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.x = window_width / 2 - (dst.w / 2);
	dst.y = window_height / 2 - (dst.h / 2);
	SDL_RenderCopy(renderer, game_over_sprite->getTexture(),
		game_over_sprite->getRect(), &dst);
}

void Game::renderFrame() {
	
	SDL_RenderClear(renderer);
	Vec2 camPos = Camera::CameraControl.GetPos();
	area.render(renderer, camPos);
	for (auto& entity : entities) {
        entity->render(renderer,camPos);
    }
    if(game_over_bool){
		renderGameOver(renderer, game_over_sprite);
    }

//Don't forget too free your surface and texture
    SDL_RenderPresent(renderer);
}

void Game::spawn_enemies() {
    auto player=entities.front();
    //ToDo check if enemy is generated on wall or not
    for (int i = 0; i < 10*wave; i++) {
        int pos_x=get_int_random(0, map_width * 3);
        int pos_y=get_int_random(0, map_width * 3);

        if(abs(pos_x-player->getPos().x) < 3 || abs(pos_y-player->getPos().y) < 3)
        {
            i--; continue;
        }
        entities.push_back(
                std::make_shared<Enemy>(*this,
                                        Vec2(pos_x,pos_y),
                                        entities.front(),
                                        get_double_random(wave, 2 * wave),
                                        50 * wave)
        );
    }
    wave++;
}

void Game::do_damage(int hp, std::vector<Vec2> points, Entity * damage_dealer){
    std::vector<std::shared_ptr<Entity> > dead_counter=std::vector<std::shared_ptr<Entity> >();
    for(auto& entity : entities){
        for(auto & point : points){
            if(damage_dealer!= nullptr && entity->equals(damage_dealer)) continue;
            else{
                if(entity->getPos().x==point.x && entity->getPos().y==point.y) {
                    entity->damage(hp);
                }
            }
        }
    }
}

void Game::add_projectile(std::vector<std::shared_ptr<Entity> > projectiles) {
    for(auto projectile : projectiles)
        entities.push_back(projectile);
}

void Game::game_over() {
    game_over_bool=true;
}



//invariant is that the first element is the player
//we need to change that, the whole structor is still messy
bool Game::saveState(std::string filename) {

	std::fstream file{ filename, std::fstream::in | std::fstream::out | std::fstream::trunc};
	file << Game::timer.get_elapsed_time() << std::endl;
	file << game_over_bool << std::endl;
	file << current_area << std::endl;
	file << wave << std::endl;
	for (auto& e : entities) {
		e->serialize(file);
	}
	return true;
}

int readLineAndConvertToInt(std::fstream& f) {
	std::string line;
	std::getline(f, line);
	return std::stoi(line);
}

int readLineAndConvertToLongLong(std::fstream& f) {
	std::string line;
	std::getline(f, line);
	return std::stoll(line);
}

void Game::loadState(std::string filename) {
	entities.clear();
	dead_entities.clear();
	std::fstream file{ filename, std::fstream::in};
	std::string line;
	long long elapsed = readLineAndConvertToLongLong(file);
	Game::timer.setTimerTo(elapsed);
	game_over_bool = readLineAndConvertToInt(file);
	std::getline(file, line);
	current_area = line;
	area.load(this->getResourceLoader(), current_area);
	logic.load(area);
	wave = readLineAndConvertToInt(file);
	
	//load entities
	EntityType type = (EntityType)readLineAndConvertToInt(file);
	//TODO make exception meaningfull...convention is that first serialized object must be a player
	if (type != player) throw 11;
	auto p = std::make_shared<Player>(Player::deserialize(file, *this));
	entities.push_back(p);
	while (std::getline(file, line)) {
		type = (EntityType)std::stoi(line);
		if (type == projectile) {
			auto pro = std::make_shared<Projectile>(Projectile::deserialize(file, *this));
			entities.push_back(pro);
		}
		else if (type == enemy) {
			auto enemy = std::make_shared<Enemy>(Enemy::deserialize(file, *this, p));
			entities.push_back(enemy);
		}
	}


}

void Game::getFileNameInput(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z && filename.length() < 20
                ) {
            filename += SDL_GetKeyName(e.key.keysym.sym);
            menu_stack.back().menu_items.back().changeName(filename);
        } else if (e.key.keysym.sym == SDLK_RETURN) {
            saveState(menu_stack.back().path_to_save + filename + ".txt");
            menu_stack.pop_back();
            filename = "";
        } else if (e.key.keysym.sym == SDLK_ESCAPE) {
            menu_stack.pop_back();
            filename = "";
        } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
            filename = filename.substr(0, filename.length()-1);
            menu_stack.back().menu_items.back().changeName(filename);
        }
    } else if (e.type == SDL_QUIT ) {
        running = false;
        INFO("Received 'quit' signal.");
    }
    save_menu.menu_items.back().changeName(filename);
}

void Game::setLoadMenuItems(std::string name) {
    load_menu.menu_items.clear();
    load_menu.addElement(*new MenuItem("Select a game to be load", Blue, false, true));
    for (fs::directory_iterator itr(name); itr!=fs::directory_iterator(); ++itr)
        if (fs::is_regular_file(itr->status()))
            load_menu.addElement(*new MenuItem(itr->path().filename().string(), Blue, true, true));

    load_menu.actual_element = 1;
}

