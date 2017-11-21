#include "entities/player.h"

#include <SDL.h>

#include "enviorment_variables.h"
#include "game.h"
#include <vector>
#include "sprite_set.h"
#include "entities/projectile.h"


Player::Player(Game& game, Vec2 pos) : Entity(game, pos, "player.png") {
    sprite_set->set_texture_map({2,1,0,3});
    sprite_set->update_texture(Direction::south);
}

Player::Player(Game& game, Vec2 pos, const int hp) : Entity(game, pos, "player.png", hp) {
    sprite_set->set_texture_map({2,1,0,3});
    sprite_set->update_texture(Direction::south);
}


void Player::update() {
    for (auto const& e : game.getEvents()) {
        if (e.type != SDL_KEYDOWN) {
            continue;
        }
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                this->direction=Direction::north;
                move(this->movement_speed);
                break;
            case SDLK_DOWN:
                this->direction=Direction::south;
                move(this->movement_speed);
                break;
            case SDLK_LEFT:
                this->direction=Direction::west;
                move(this->movement_speed);
                break;
            case SDLK_RIGHT:
                this->direction=Direction::east;
                move(this->movement_speed);
                break;
            case SDLK_SPACE:
                attack();
                break;
            case SDLK_1:
                this->weaponIndex = 0;
                break;
            case SDLK_2:
                this->weaponIndex = 1;
                break;
            case SDLK_3:
                this->weaponIndex = 2;
                break;

        }

    }
    this->sprite_set->update_texture(this->direction);

}

void Player::attack() {
    std::vector<std::shared_ptr<Entity> > projectiles=std::vector<std::shared_ptr<Entity> >();
	auto& weapon = this->equipedWeapons[this->weaponIndex];
	if (!weapon.readyToShoot()) return;
	weapon.updateShotTimer();
	auto hitten_fields = weapon.GetHitedFields(this->direction);
	for (auto& vec : hitten_fields) {
		vec.x += this->pos.x;
		vec.y = this->pos.y - vec.y;
		projectiles.push_back(std::make_shared<Projectile>(game, vec, weapon.GetTexType(), this->direction));
	}
    game.do_damage(weapon.GetDmg(),hitten_fields,this);
    game.add_projectile(projectiles);
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

void Player::damage(int hp) {
    this->hp-=hp;
    if (this->hp <= 0) game.game_over();
}
