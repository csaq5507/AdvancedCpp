#include "entities/enemy.h"

#include <SDL.h>
#include "game.h"
#include <string>
#include "sprite_set.h"

Enemy::Enemy(Game& game, Vec2 pos, std::shared_ptr<Entity> player, int speed) : Entity(game, pos, std::string("monster")+std::to_string(pos.x%4+1)+std::string(".png")), move_timer(std::chrono::high_resolution_clock::now()),rng(0,4) {
    this->sprite_set->setRect(0, 0, tile_size,tile_size);
    this->speed = speed;
    this->player = player;
}

Enemy::Enemy(Game& game, Vec2 pos, std::shared_ptr<Entity> player, int speed, const int hp) : Entity(game, pos, std::string("monster")+std::to_string(pos.x%4+1)+std::string(".png"),hp), move_timer(std::chrono::high_resolution_clock::now()),rng(0,4) {
    this->sprite_set->setRect(0, 0, tile_size,tile_size);
    this->speed = speed;
    this->player = player;
}

void Enemy::update() {
    if(timer.get_current_time()>move_timer) {
        move_timer = timer.get_current_time() + timer.milliseconds(speed);
        if (dist_to_player() < 5) {
            get_player_direction();
            move(1);
        } else {
            this->direction=Direction(rng(rnd));
            switch(this->direction)
            {
                case Direction::north: this->sprite_set->setRect(0,3*tile_size,tile_size,tile_size); break;
                case Direction::south: this->sprite_set->setRect(0, 0, tile_size,tile_size); break;
                case Direction::east: this->sprite_set->setRect(0, 2*tile_size, tile_size,tile_size); break;
                case Direction::west: this->sprite_set->setRect(0, 1*tile_size, tile_size,tile_size); break;
            }
            move(rng(rnd)<2?-1:1);
        }
        if (is_on_player()) {
            player->damage(1000);
        }

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

int Enemy::dist_to_player() {
    Vec2 position_player = player->getPos();
    float diff_y = position_player.y - pos.y;
    float diff_x = position_player.x - pos.x;
    return sqrt((diff_y * diff_y) + (diff_x * diff_x));
}

void Enemy::get_player_direction() {
    Vec2 position_player = player->getPos();
    float diff_y = position_player.y - pos.y;
    float diff_x = position_player.x - pos.x;
    if (diff_y == 0) {
        this->direction = diff_x<0?Direction::west:Direction::east;
    } else if (diff_x == 0) {
        this->direction = diff_y<0?Direction::north:Direction::south;
    } else if (abs(diff_y) <= abs(diff_x)) {
        this->direction = diff_y<0?Direction::north:Direction::south;
    } else {
        this->direction = diff_x<0?Direction::west:Direction::east;
    }
}

bool Enemy::is_on_player() {
    Vec2 position_player = player->getPos();
    return (((position_player.y - pos.y) == 0) && ((position_player.x - pos.x) == 0));
}