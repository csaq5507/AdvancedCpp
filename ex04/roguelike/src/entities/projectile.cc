#include "entities/projectile.h"

#include <SDL.h>

#include "enviorment_variables.h"
#include "game.h"
#include <vector>
#include "sprite_set.h"

Projectile::Projectile(Game& game, Vec2 pos,Weapon w_type) : Entity(game, pos, ((w_type==Weapon::melee)?"melee.png":((w_type==Weapon::flint)?"flint.png":"pumpgun.png"))), existence_timer(std::chrono::high_resolution_clock::now()+timer.milliseconds(200)) {
    sprite_set->setRect(0, 0, tile_size,tile_size);

}

void Projectile::update() {
    if(timer.get_current_time()>existence_timer)
    {
        std::vector<Vec2> range;
        range.push_back(Vec2(this->getPos().x,this->getPos().y));
        this->hp=0;
    }
}


void Projectile::render(SDL_Renderer* renderer, const Vec2& cameraPos){
    SDL_Rect dst;
    dst.x = (this->getPos().x * tile_size ) - cameraPos.x;
    dst.y = (this->getPos().y * tile_size) - cameraPos.y;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}
