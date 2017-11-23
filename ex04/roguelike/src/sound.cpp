//
// Created by ivan on 23/11/17.
//

#include "sound.h"

sounds::sounds() {
    sound_chunk=NULL;
    musik_chunk=NULL;
    walk_chunk=NULL;
    walk_channel=-1;
}

void sounds::play_attack_sound(const char *filename)
{
    sound_chunk = Mix_LoadWAV(filename);
    Mix_PlayChannel(-1, sound_chunk, 0);
}

void sounds::play_musik()
{
    if(musik_chunk==NULL)
        musik_chunk = Mix_LoadWAV(MUSIK);
    Mix_PlayChannel(-1, musik_chunk, -1);
}

void sounds::stop_musik()
{
    if(musik_chunk==NULL)
        musik_chunk = Mix_LoadWAV(MUSIK);
    Mix_PlayChannel(-1, musik_chunk, -1);
}

void sounds::toggle_walk(bool walk)
{
    if(walk_chunk==NULL) {
        walk_chunk = Mix_LoadWAV(PLAYER_WALK_SOUND);
    }
    if(walk && walk_channel==-1)
        walk_channel=Mix_PlayChannel(-1,walk_chunk,-1);
    else if(!walk)
    {
        Mix_HaltChannel(walk_channel);
        walk_channel=-1;
    }
}