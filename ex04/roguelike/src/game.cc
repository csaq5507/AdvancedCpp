#include "game.h"

#include "entities/player.h"
#include "entities/enemy.h"
#include "utils/logging.h"
#include <random>


const int WINDOW_NUM_SPRITES_WIDTH = 15;
const int WINDOW_NUM_SPRITES_HEIGHT = 15;

const int WINDOW_WIDTH = WINDOW_NUM_SPRITES_WIDTH * SPRITE_SIZE;
const int WINDOW_HEIGHT = WINDOW_NUM_SPRITES_HEIGHT * SPRITE_SIZE;

Game::Game() {
    window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    // spawn player
    entities.push_back(std::make_shared<Player>(*this, Vec2{5, 5}));
    generateEnemies();
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
    }
}

void Game::renderFrame() {
    SDL_RenderClear(renderer);

    for (auto& entity : entities) {
        SDL_Rect dst;
        dst.x = entity->getPos().x * SPRITE_SIZE;
        dst.y = entity->getPos().y * SPRITE_SIZE;
        dst.w = SPRITE_SIZE;
        dst.h = SPRITE_SIZE;

        auto sprite_set = entity->getSpriteSet();
        SDL_RenderCopy(renderer, sprite_set->getTexture(),
                       sprite_set->getRect(), &dst);
    }

    SDL_RenderPresent(renderer);
}

void Game::generateEnemies() {
    int numEnemies = 5;//rand() % 100 + 1;
    std::default_random_engine rnd;
    std::uniform_int_distribution<int> rng(0,10);
    for (int i = 0; i < numEnemies; i++)
        entities.push_back(std::make_shared<Enemy>(*this, Vec2{rng(rnd), rng(rnd)}));

}

void Game::do_damage(int hp, std::vector<Vec2> points, Entity * damage_dealer){
    std::vector<std::shared_ptr<Entity> > dead_counter=std::vector<std::shared_ptr<Entity> >();
    int counter=0;
    for(auto& entity : entities){
        for(auto & point : points){
            if(entity->equals(damage_dealer)) continue;
            else{
                if(entity->getPos().x==point.x && entity->getPos().y==point.y) {
                    entity->damage(hp);
                    if(entity->is_dead()) dead_counter.push_back(entity);
                }
            }
        }
        counter++;
    }
    for(int i=0;i<dead_counter.size();i++)
    {
        entities.remove(dead_counter[i]);
    }
}
