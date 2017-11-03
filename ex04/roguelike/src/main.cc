#include <cstdlib>

#include <SDL.h>
#include <SDL_image.h>

#include "game.h"
#include "utils/logging.h"

class Runtime {
  public:
    Runtime() {
        if (SDL_Init(SDL_INIT_VIDEO)) {
            FATAL("Could not initialize SDL: %s", SDL_GetError());
        }

        int img_flags = IMG_INIT_PNG;
        if ((IMG_Init(img_flags) & img_flags) != img_flags) {
            FATAL("Could not initialize SDL_image: %s", IMG_GetError());
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
        game.clearEvents();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            game.addEvent(e);
        }

        game.updateEntities();

        game.renderFrame();
    }

    return EXIT_SUCCESS;
}
