#include "entities/enemy.h"
#include "game.h"
#include "utils/random.h"



Enemy::Enemy(Game& game, Vec2 pos, std::shared_ptr<Entity> player, const double movement_speed) :
        Entity(game, pos, std::string("monster")+std::to_string(pos.x%4+1)+std::string(".png"),100,movement_speed),
        player(player),
        enemy_move_timer(0)
{
    this->sprite_set->set_texture_map({3,2,0,1});
}

Enemy::Enemy(Game& game, Vec2 pos, std::shared_ptr<Entity> player, const double movement_speed, const int hp) :
        Entity(game, pos, std::string("monster")+std::to_string(pos.x%4+1)+std::string(".png"),hp,movement_speed),
        player(player),
        enemy_move_timer(0)
{
    this->sprite_set->set_texture_map({3,2,0,1});
}

void Enemy::update() {
    if(Game::timer.get_elapsed_time() > enemy_move_timer) {
        long long int delay=( Game::timer.milliseconds(1000).count() / movement_speed );
        enemy_move_timer = Game::timer.get_elapsed_time() + ( (fast) ? delay*2 : delay*4 ) ;
        if (dist_to_player() < 7) {
            get_player_direction();
            this->fast=true;
        } else {
            this->direction=Direction(get_int_random(0,3));
            this->fast=false;
        }
        this->sprite_set->update_texture(this->direction);
        move();

    }

    if (is_on_player()) {
        player->damage(1000);
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
    float diff_y = (float)(position_player.y - pos.y);
    float diff_x = (float)(position_player.x - pos.x);
    return (int)sqrt((diff_y * diff_y) + (diff_x * diff_x));
}

void Enemy::get_player_direction() {
    Vec2 position_player = player->getPos();
    float diff_y = (float)(position_player.y - pos.y);
    float diff_x = (float)(position_player.x - pos.x);
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

void Enemy::serialize(std::fstream& f) {
	f << enemy << std::endl;
	Entity::serialize(f);
	f << this->movement_speed << std::endl;
}

//convention type was already read
Enemy Enemy::deserialize(std::fstream& f, Game& game, std::shared_ptr<Player>& player) {
	std::string line;
	Vec2 pos;
	int hp;
	Direction dir;
	//read entity
	std::getline(f, line);
	pos.x = std::stoi(line);
	std::getline(f, line);
	pos.y = std::stoi(line);
	std::getline(f, line);
	hp = std::stoi(line);
	std::getline(f, line);
	dir = (Direction)std::stoi(line);
	//read enemy
	std::getline(f, line);
	int speed = std::stoi(line);
	Enemy e{ game, pos, player, speed, hp };
	e.direction = dir;
	return e;
}
