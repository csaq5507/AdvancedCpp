#include "entities/enemy.h"

#include <SDL.h>
#include "game.h"
#include "sprite_set.h"

Enemy::Enemy(Game& game, Vec2 pos, std::shared_ptr<Entity> player) : Entity(game, pos, "player2.png"), move_timer(std::chrono::high_resolution_clock::now()),rng(0,4) {
    sprite_set->setRect(0, 0, tile_size,tile_size);
    speed = 1;//rand() % 10 + 1;
    this->player = player;
}

void Enemy::update() {
    if(timer.get_current_time()>move_timer) {
        move_timer = timer.get_current_time() + timer.seconds(speed);
        if (dist_to_player() < 5) {
            move(get_player_direction());
        } else {
            this->direction=Direction(rng(rnd));
            move(rng(rnd)<2?-1:1);
        }
        if (is_on_player()) {
            player->damage(1000);
        }

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

int Enemy::dist_to_player() {
    Vec2 position_player = player->getPos();
    float diff_y = position_player.y - pos.y;
    float diff_x = position_player.x - pos.x;
    return sqrt((diff_y * diff_y) + (diff_x * diff_x));
}

Direction Enemy::get_player_direction() {
    Vec2 position_player = player->getPos();
    float diff_y = position_player.y - pos.y;
    float diff_x = position_player.x - pos.x;
    if (diff_y == 0) {
        return (diff_x<0?Direction::north:Direction::south);
    } else if (diff_x == 0) {
        return (diff_y<0?Direction::west:Direction::east);
    } else if (abs(diff_y) <= abs(diff_x)) {
        return (diff_y<0?Direction::west:Direction::east);
    } else {
        return (diff_x<0?Direction::north:Direction::south);
    }
}

bool Enemy::is_on_player() {
    Vec2 position_player = player->getPos();
    return (((position_player.y - pos.y) == 0) && ((position_player.x - pos.x) == 0));
}