#ifndef ROGUELIKE_ENTITIES_ENEMY_H_
#define ROGUELIKE_ENTITIES_ENEMY_H_

#include "entity.h"
#include "entities/player.h"
#include <fstream>
class Player;
class Enemy : public Entity {
private:
    std::shared_ptr<Entity> player;
	long long int enemy_move_timer;
    int dist_to_player();
    void get_player_direction();
    bool is_on_player();
public:

    void render(SDL_Renderer* renderer, const Vec2& cameraPos);
    Enemy(Game &game, Vec2 pos, std::shared_ptr<Entity> player, const double movement_speed);
    Enemy(Game &game, Vec2 pos, std::shared_ptr<Entity> player, const double movement_speed, const int hp);

    void update() override;
	void serialize(std::fstream& f);
	static Enemy deserialize(std::fstream& f, Game& game, std::shared_ptr<Player>& player);
};

#endif  // ROGUELIKE_ENTITIES_ENEMY_H_
