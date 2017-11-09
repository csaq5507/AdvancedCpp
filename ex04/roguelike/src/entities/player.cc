#include "entities/player.h"

#include <SDL.h>

#include "enviorment_variables.h"
#include "game.h"
#include <vector>
#include "sprite_set.h"

Player::Player(Game& game, Vec2 pos) : Entity(game, pos, "player.png"), attack_timer(std::chrono::high_resolution_clock::now()),weapon(Weapon::melee) {
    sprite_set->setRect(0, 0, tile_size,tile_size);

}

Player::Player(Game& game, Vec2 pos, const int hp) : Entity(game, pos, "player.png", hp),attack_timer(std::chrono::high_resolution_clock::now()),weapon(Weapon::melee) {
    sprite_set->setRect(0, 0, tile_size,tile_size);
}


void Player::update() {
    for (auto const& e : game.getEvents()) {
        if (e.type != SDL_KEYDOWN) {
            continue;
        }

        switch (e.key.keysym.sym) {
            case SDLK_UP: move({0, -1}); break;
            case SDLK_DOWN: move({0, 1}); break;
            case SDLK_LEFT: move({-1, 0}); break;
            case SDLK_RIGHT: move({1, 0}); break;
            case SDLK_SPACE: attack(); break;
            case SDLK_0: weapon=Weapon::melee; break;
            case SDLK_1: weapon=Weapon::flint; break;
        }

    }
}

void Player::attack() {
    if(timer.get_current_time()>attack_timer) {
        attack_timer=timer.get_current_time()+ timer.seconds(1);
        std::vector<Vec2> hitten_fields=std::vector<Vec2>();
        switch (weapon) {
            case Weapon::melee:

                for(int i=this->pos.x-1;i<=this->pos.x+1;i++)
                    for(int j=this->pos.y-1;j<=this->pos.y+1;j++)
                        hitten_fields.push_back(Vec2({i,j}));

                game.do_damage(100,hitten_fields,this);

                break;
            case Weapon::flint:
                for(int i=this->pos.x;i<=this->pos.x+100;i++)
                        hitten_fields.push_back(Vec2({i,this->pos.y}));
                game.do_damage(50,hitten_fields,this);
                break;
        }
    }
}


void Player::render(SDL_Renderer* renderer, Camera c){
    SDL_Rect dst;
    dst.x = window_width / 2;
    dst.y = window_height/2;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}

