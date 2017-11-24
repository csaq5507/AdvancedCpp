//
// Created by ivan on 23/11/17.
//

#include "sound.h"
#include <iostream>
sounds::sounds() : sound(true),music(true) {
    sound_chunk=NULL;
    musik_chunk=NULL;
    walk_chunk=NULL;
    walk_channel=-1;
}

void sounds::play_attack_sound(const char *filename)
{
    if(sound){
        sound_chunk = Mix_LoadWAV(filename);
        Mix_PlayChannel(-1, sound_chunk, 0);

    }
}

void sounds::play_music()
{
    if(musik_chunk==NULL)
        musik_chunk = Mix_LoadWAV(MUSIK);

     musik_channel=Mix_PlayChannel(-1, musik_chunk, -1);
}

void sounds::stop_music()
{
    Mix_HaltChannel(musik_channel);
}

void sounds::toggle_music() {
    if(music){
        music=false;
        stop_music();
    }   else
    {
        music=true;
        play_music();
    }
}

void sounds::toggle_sound() {
    if(sound)
        sound=false;
    else
        sound=true;
}

void sounds::toggle_walk(bool walk)
{
    if(sound) {

        if (walk_chunk == NULL) {
            walk_chunk = Mix_LoadWAV(PLAYER_WALK_SOUND);
        }
        if (walk && walk_channel == -1)
            walk_channel = Mix_PlayChannel(-1, walk_chunk, -1);
        else if (!walk && walk_channel != -1) {
            Mix_HaltChannel(walk_channel);
            walk_channel = -1;
        }
    }
}