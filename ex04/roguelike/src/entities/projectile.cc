#include "entities/projectile.h"

#include <SDL.h>

#include "enviorment_variables.h"
#include "game.h"
#include <vector>
#include "sprite_set.h"

Projectile::Projectile(Game& game, Vec2 pos, Projectile_Type type) : Entity(game, pos, "player.png"), travel_timer(std::chrono::high_resolution_clock::now()), type(type) {
    sprite_set->setRect(0, 0, tile_size,tile_size);

}

void Projectile::update() {
    switch(type){
        case Projectile_Type::hitscan:
            break;
        case Projectile_Type::projectile:
            break;
    }
}


void Projectile::render(SDL_Renderer* renderer, Camera c){
    SDL_Rect dst;
    dst.x = (this->getPos().x * tile_size ) - c.GetPos().x;
    dst.y = (this->getPos().y * tile_size) - c.GetPos().y;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}
