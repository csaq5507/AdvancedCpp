#include "entities/player.h"

#include <SDL.h>

#include "game.h"
#include "sprite_set.h"

Player::Player(Game& game, Vec2 pos) : Entity(game, pos, "player.png"), attack_timer(std::chrono::high_resolution_clock::now()),weapon(Weapon::melee) {
    sprite_set->setRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
}

Player::Player(Game& game, Vec2 pos, const int hp) : Entity(game, pos, "player.png", hp),attack_timer(std::chrono::high_resolution_clock::now()),weapon(Weapon::melee) {
    sprite_set->setRect(0, 0, SPRITE_SIZE, SPRITE_SIZE);
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
        attack_timer=timer.get_current_time()+timer.one_second();
        switch (weapon) {
            case Weapon::melee:

                break;
            case Weapon::flint:

                break;
        }
    }
}
