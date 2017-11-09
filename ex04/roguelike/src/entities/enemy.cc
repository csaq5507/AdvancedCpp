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

        Vec2 move_horizontally = Vec2({(rng(rnd)==0?-1:1),0});
        Vec2 move_vertically = Vec2({0,(rng(rnd)==0?-1:1)});
        move((rng(rnd)==0)?move_horizontally:move_vertically);
    }
}


void Enemy::render(SDL_Renderer* renderer, const Vec2& cameraPos){
    SDL_Rect dst;
	//The camera vector points to the lef upper vertex where we start render
	//hence we need to offset the position of the enemys to render them in the correnct pixel coordinates
    dst.x = (this->getPos().x * tile_size) - cameraPos.x;
    dst.y = (this->getPos().y * tile_size) - cameraPos.y;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}
