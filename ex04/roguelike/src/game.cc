#include "game.h"
#include <iostream>
#include <fstream>
#include "utils/logging.h"
#include "utils/random.h"
#include "entities/projectile.h"
#include <math.h>
#include "SDL_ttf.h"

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

    menuItems.push_back("Start New Game");
    menuItems.push_back("Resume");
    menuItems.push_back("Load Game");
    menuItems.push_back("Save Game");
    menuItems.push_back("Exit");

    filename = "";
}

void Game::clearGame() {
    wave = 0;
    entities.clear();
    entities.push_back(std::make_shared<Player>(*this, Vec2{5, 5}));
    auto player = entities.front();
    Camera::CameraControl.mode = TARGET_MODE_CENTER;
    Camera::CameraControl.SetTarget(player);
    spawn_enemies();
    menuItems.clear();
}

void Game::mainLoop() {

        clearEvents();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            addEvent(e);
        }

    if (!menuOpen) {
        updateEntities();
        renderFrame();
    } else if (saveMenu) {
        renderSaveMenu();
    } else if (loadMenu) {
        renderSaveMenu();
    } else {
        renderMainMenu();
    }
}

void Game::addEvent(SDL_Event e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && menuOpen && !saveMenu && !loadMenu) {
        running = false;
    } else if (saveMenu) {
        getFileNameInput(e);
    } else if (loadMenu) {

    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        pause = true;
        menuOpen = true;
        return;
    } else if (e.type == SDL_QUIT ) {
        running = false;
        INFO("Received 'quit' signal.");
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN && menuOpen && menuSelector != menuItems.size()-1) {
        if ((menuItems.at(menuSelector + 1) == "Resume" || menuItems.at(menuSelector + 1) == "Save Game") && !pause)
            menuSelector += 2;
        else
            menuSelector++;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP && menuOpen && menuSelector != 0) {
        if ((menuItems.at(menuSelector - 1) == "Resume" || menuItems.at(menuSelector - 1) == "Save Game") && !pause)
            menuSelector -= 2;
        else
            menuSelector--;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && menuOpen) {
        if (menuItems.at(menuSelector) == "Start New Game") {
            pause = false;
            menuOpen = false;
            clearGame();
            init();
            INFO("New Game started.");
        } else if (menuItems.at(menuSelector) == "Resume") {
            pause = false;
            menuOpen = false;
        } else if (menuItems.at(menuSelector) == "Load Game") {

        } else if (menuItems.at(menuSelector) == "Save Game") {
            saveMenu = true;
        } else if (menuItems.at(menuSelector) == "Exit") {
            running = false;
            INFO("Game closed.");
        }
    }

    events.push_back(std::move(e));
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
                                        get_int_random(1500, 3000),
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

void Game::renderMainMenu() {
    SDL_RenderClear(renderer);
    /**
     * An example how to use sdlttf
     *
     */

    TTF_Font* Sans = TTF_OpenFont("resources/sunvalley.ttf", 112); //this opens a font style and sets a size
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    SDL_Rect Message_rect;
    for(unsigned i = 0; i < menuItems.size(); i++){
            if (i == menuSelector)
                surfaceMessage = TTF_RenderText_Solid(Sans, menuItems.at(i).c_str(), Red);
            else if ((menuItems.at(i) == "Resume" || menuItems.at(i) == "Save Game") && !pause)
                surfaceMessage = TTF_RenderText_Solid(Sans, menuItems.at(i).c_str(), Gray);
            else
                surfaceMessage = TTF_RenderText_Solid(Sans, menuItems.at(i).c_str(), Blue);
            Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            Message_rect.x = 450;
            Message_rect.y = 100 + i * 150;
            Message_rect.w = 300;
            Message_rect.h = 100;
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    }

    SDL_RenderPresent(renderer);
}

void Game::renderSaveMenu() {
    SDL_RenderClear(renderer);
    /**
     * An example how to use sdlttf
     *
     */

    TTF_Font* Sans = TTF_OpenFont("resources/sunvalley.ttf", 112); //this opens a font style and sets a size
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    SDL_Rect Message_rect;

    surfaceMessage = TTF_RenderText_Solid(Sans, "Enter a name for the game", Red);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    Message_rect.x = 450;
    Message_rect.y = 100;
    Message_rect.w = 300;
    Message_rect.h = 100;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    surfaceMessage = TTF_RenderText_Solid(Sans, filename.c_str(), Red);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    Message_rect.x = 600 - 10 * filename.length();
    Message_rect.y = 350;
    Message_rect.w = 20 * filename.length();
    Message_rect.h = 100;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_RenderPresent(renderer);
}

void Game::renderLoadMenu() {
    //ToDo
    //Get list of all saved files
}

void Game::getFileNameInput(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z && filename.length() < 38) {
            filename += SDL_GetKeyName(e.key.keysym.sym);
        } else if (e.key.keysym.sym == SDLK_RETURN) {
            saveMenu = false;
            filename = "";
        } else if (e.key.keysym.sym == SDLK_ESCAPE) {
            saveMenu = false;
            filename = "";
        } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
            filename = filename.substr(0, filename.length()-1);
        }
    } else if (e.type == SDL_QUIT ) {
        running = false;
        INFO("Received 'quit' signal.");
    }
}