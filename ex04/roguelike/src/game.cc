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

}

void Game::addEvent(SDL_Event e) {
    if (e.type == SDL_QUIT ||
        (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
        INFO("Received 'quit' signal.");
        running = false;
        return;
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



  //  Mix_Music * music = Mix_LoadMUS("resources/music.ogg");
  //  if (music == NULL)
  //      return ;

    /**
     * An example how to use sdlttf
     *
     */

    TTF_Font* Sans = TTF_OpenFont("resources/sunvalley.ttf", 24); //this opens a font style and sets a size

    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Hallo", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

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