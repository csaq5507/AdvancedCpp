#include "entities/enemy.h"

#include <SDL.h>
#include "game.h"
#include "sprite_set.h"

Enemy::Enemy(Game& game, Vec2 pos) : Entity(game, pos, "player2.png"), move_timer(std::chrono::high_resolution_clock::now()),rng(0,1) {
    sprite_set->setRect(0, 0, tile_size,tile_size);

}

void Enemy::update() {

    if(timer.get_current_time()>move_timer) {
        move_timer = timer.get_current_time() + timer.seconds(2);
        move((rng(rnd)==0)?Vec2({(rng(rnd)==0?-1:1),0}):Vec2({0,(rng(rnd)==0?-1:1)}));
    }
}


void Enemy::render(SDL_Renderer* renderer,Camera c){
    SDL_Rect dst;
    dst.x = (this->getPos().x * tile_size ) - c.GetPos().x;
    dst.y = (this->getPos().y * tile_size) - c.GetPos().y;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}
