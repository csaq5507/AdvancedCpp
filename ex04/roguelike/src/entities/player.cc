#include "entities/player.h"

#include <SDL.h>

#include "game.h"
#include "sprite_set.h"

Player::Player(Game& game, Vec2 pos) : Entity(game, pos, "player.png") {
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
        }
    }
}
