//
// Created by ivan on 22/11/17.
//

#ifndef ADVANCEDCPP_SOUND_H
#define ADVANCEDCPP_SOUND_H

#include "SDL2/SDL.h"
#include <unistd.h>

#include "SDL2/SDL_mixer.h"

class sounds
{
public:
    static sounds& getInstance()
    {
        static sounds instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
private:

    Mix_Chunk * sound_chunk;
    Mix_Chunk * musik_chunk;
    Mix_Chunk * walk_chunk;

    int walk_channel;

    sounds();

public:
    static constexpr char PLAYER_WALK_SOUND[] = "resources/sounds/walk1.wav";
    static constexpr char MONSTER_WALK_SOUND[] = "resources/sounds/walk2.wav";
    static constexpr char MELEE_SOUND[] = "resources/sounds/melee.wav";
    static constexpr char FLINT_SOUND[] = "resources/sounds/flint.wav";
    static constexpr char PUMPGUN_SOUND[] = "resources/sounds/pumpgun.wav";
    static constexpr char MUSIK[] = "resources/sounds/music.wav";


    sounds(sounds const&)          = delete;
    void operator=(sounds const&)  = delete;


    void play_attack_sound(const char* filename);
    void play_musik();
    void stop_musik();
    void toggle_walk(bool walk);
};

#endif //ADVANCEDCPP_SOUND_H
