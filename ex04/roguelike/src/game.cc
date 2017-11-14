#include "game.h"

#include "utils/logging.h"
#include "utils/random.h"

#include <math.h>


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
    if(game_over_bool){
        SDL_Rect dst;
        SDL_QueryTexture(game_over_sprite->getTexture(), nullptr, nullptr,&dst.w,&dst.h);
        dst.x = window_width / 2 - (dst.w/2);
        dst.y = window_height / 2 - (dst.h/2);
        SDL_RenderCopy(renderer, game_over_sprite->getTexture(),
                       game_over_sprite->getRect(), &dst);
    }
    SDL_RenderPresent(renderer);
}

void Game::spawn_enemies() {
    auto player=entities.front();
    //ToDo check if enemy is generated on wall or not
    for (int i = 0; i < 1*wave; i++) {
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
                                        get_int_random(600, 1500),
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
