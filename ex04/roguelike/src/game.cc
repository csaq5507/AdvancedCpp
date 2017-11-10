#include "game.h"

#include "enviorment_variables.h"
#include "entities/enemy.h"
#include "entities/projectile.h"
#include "utils/logging.h"
#include <random>



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
	area.load(*resource_loader, "1.area");
	//load logic map
	logic.load("1.area");
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

void Game::renderFrame() {
	
	SDL_RenderClear(renderer);
	Vec2 camPos = Camera::CameraControl.GetPos();
	area.render(renderer, camPos);
	for (auto& entity : entities) {
        entity->render(renderer,camPos);
    }
    SDL_RenderPresent(renderer);
}

void Game::spawn_enemies() {
    std::default_random_engine rnd;
    std::uniform_int_distribution<int> rng_width(0,map_width*3);
    std::uniform_int_distribution<int> rng_high(0,map_height*3);
    std::uniform_int_distribution<int> rng_speed(350,1500);//000*wave);

    //ToDo check if enemy is generated on wall or not
    for (int i = 0; i < 10*wave; i++)
        entities.push_back(std::make_shared<Enemy>(*this, Vec2{rng_width(rnd), rng_high(rnd)}, entities.front(), rng_speed(rnd),50*wave));

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

void Game::add_projectile(Weapon w_type, std::vector<Vec2> points) {
    for(auto point : points)
        entities.push_back(std::make_shared<Projectile>(*this,point,w_type));
}

void Game::game_over() {
    // ToDo
}
