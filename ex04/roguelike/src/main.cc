#include <cstdlib>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "game.h"
#include "utils/logging.h"

class Runtime {
  public:
    Runtime() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
            FATAL("Could not initialize SDL: %s", SDL_GetError());
        }

        int img_flags = IMG_INIT_PNG;
        if ((IMG_Init(img_flags) & img_flags) != img_flags) {
            FATAL("Could not initialize SDL_image: %s", IMG_GetError());
        }
        if (TTF_Init()==-1) {
            FATAL("Could not initialize TTF: %s", TTF_GetError());
        }

        // Set up the audio stream
        int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
        if( result < 0 )
        {
            fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
            exit(-1);
        }

        result = Mix_AllocateChannels(4);
        if( result < 0 )
        {
            fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
            exit(-1);
        }


        INFO("SDL initilization done.");
    }

    ~Runtime() {
        IMG_Quit();
        SDL_Quit();
    }
};

int main(int, char* []) {
    Runtime runtime;
    Game game;

    game.init();


    while (game.isRunning()) {
        game.mainLoop();
    }

        return EXIT_SUCCESS;
}
