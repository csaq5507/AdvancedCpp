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
            case SDLK_UP: this->direction=Direction::north; move(this->movement_speed); break;
            case SDLK_DOWN: this->direction=Direction::south; move(this->movement_speed); break;
            case SDLK_LEFT: this->direction=Direction::west; move(this->movement_speed); break;
            case SDLK_RIGHT: this->direction=Direction::east; move(this->movement_speed);  break;
            case SDLK_SPACE: attack(); break;
            case SDLK_1:
                this->weapon = Weapon::melee;
                break;
            case SDLK_2:
                this->weapon = Weapon::flint;
                break;

        }

    }
}

void Player::attack() {
    if(timer.get_current_time()>attack_timer) {
        attack_timer=timer.get_current_time()+ timer.seconds(1);
        std::vector<Vec2> hitten_fields=std::vector<Vec2>();
        switch (this->weapon) {
            case Weapon::melee:

                switch(this->direction)
                {
                    case Direction::north:
                        hitten_fields.push_back(Vec2(this->pos.x-1,this->pos.y-1));
                        hitten_fields.push_back(Vec2(this->pos.x,this->pos.y-1));
                        hitten_fields.push_back(Vec2(this->pos.x+1,this->pos.y-1));
                        break;
                    case Direction::east:
                        hitten_fields.push_back(Vec2(this->pos.x+1,this->pos.y-1));
                        hitten_fields.push_back(Vec2(this->pos.x+1,this->pos.y));
                        hitten_fields.push_back(Vec2(this->pos.x+1,this->pos.y+1));
                        break;
                    case Direction::south:
                        hitten_fields.push_back(Vec2(this->pos.x-1,this->pos.y+1));
                        hitten_fields.push_back(Vec2(this->pos.x,this->pos.y+1));
                        hitten_fields.push_back(Vec2(this->pos.x+1,this->pos.y+1));
                        break;
                    case Direction::west:
                        hitten_fields.push_back(Vec2(this->pos.x-1,this->pos.y-1));
                        hitten_fields.push_back(Vec2(this->pos.x-1,this->pos.y));
                        hitten_fields.push_back(Vec2(this->pos.x-1,this->pos.y+1));
                        break;
                }
                game.do_damage(100,hitten_fields,this);
                game.add_projectile(Weapon::melee,hitten_fields);
                break;
            case Weapon::flint:
                for(int i=this->pos.x+1;i<=this->pos.x+100;i++)
                        hitten_fields.push_back(Vec2({i,this->pos.y}));
                game.do_damage(50,hitten_fields,this);
                game.add_projectile(Weapon::flint,hitten_fields);

                break;
        }
    }
}


void Player::render(SDL_Renderer* renderer, const Vec2& cameraPos){
    SDL_Rect dst;
    dst.x = window_width / 2;
    dst.y = window_height/2;
    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}

