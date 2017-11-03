# Getting Started

The string `roguelike` is just a place-holder for the name of your game.

The provided code is far from perfect but should get you started.
Examine it sceptically and use it at your own discretion.
Also note that the provide code does not conform with the Google C++ style guide.

## Sprites

Of course you can create the sprites yourself, but... I don't know about you, but I am not much of an artist.
Luckily there are a lot of 2D game assets available online, licensed under creative commons or similar.
Pick your poison.

The provided player sprite set is based on *JS Actors - Aeon Warriors Field & Battle Sprites* by JosephSeraph, licensed under [CC-BY 3.0], and available [here](https://opengameart.org/content/js-actors-aeon-warriors-field-battle-sprites)

[CC-BY 3.0]: https://creativecommons.org/licenses/by/3.0/

## Components

### `main.cc`

Here we have the initialisation of SDL components as well as the main game loop.

### `Game`

An instance of this class represents the whole game.
It implements the core functionality and owns other components like the resource loader.

Each frame all `SDL_Event`s (eg key presses) that triggered are collected and stored.

### `ResourceLoader`

An instance of this class is responsible for loading and caching resources.
At the moment the only type of resource supported is `SpriteSet`.

### `SpriteSet`

A sprite set represents a texture containing one or multiple sprites.
An instance of `SDL_Rect` is used to select a specific sprite from the set.
If `SDL_Rect` is not set (`nullptr`) the whole texture is used as one single sprite.

### `Entity`

All game entities (player, enemies, ally NPCs, ...) should be derived from this base class.
Each entity is associate with a sprite set and movement is implemented here as well.

Each frame the `update` function of each entity is called.
Here you can implement the entity's logic.

### `Player`

The player is our first game entity.
In its `update` function we iterate over the occurred `SDL_Event`s and check for key presses of the cursor keys.
If such an event is detected the entity's `move` function is invoked.

### `vec2.h`

For this kind of 2D game, 2D vectors are an essential utility in helping to keep the code base clean, simple, and readable.
Extend this class whenever need to, but choose your additions wisely as it will probably be used all over the code base.

### `logging.h`

I don't have to tell you how helpful good logging output can be.
In some cases it can even prevent the need for a debugger.
Like everything else here, the provided macros are just something to get you started.

## Encountering Errors

One essential hint for improving your development workflow:

If an error occurs, log it and recover, don't terminate the application immediately.

Take the included error sprite fore example.
If a sprite set cannot be loaded, an error is logged and the entity is given the error sprite.
If that entity's sprite is rendered the fault is immediately visible, but testing can continue.

## Framerate

Currently, the game requests SDL to use *vsync*.
This causes your game to present frames in sync with your monitor's refresh rate.

Check the frame rate if you notice high CPU usage of your game.
If *vsync* does not work for some reason you should implement a frame limiter to dynamically delay the presentation of each frame to meet the desired frame rate.

Simply using `SDL_delay` with a fixed value works too, but results in inconsistent frame pacing.

## Animations / Timings

If you decide to do animations or timing related logic, do not base your timings on the frame rate of the game -- like using a counter inside the entity's `update` function.
Write yourself a timer utility class using what is provided by `std::chrono`.

Your game should behave the same with 120 FPS as with 30 FPS.

## Building

### Visual Studio

Download the SDL2 and SDL2_Image libraries (development package, including headers and `.lib`s) and place the folders somewhere on your system.
Add 2 environment variables (`SDL2_ROOT`, `SDL2_IMAGE_ROOT`) pointing to the extracted folders.
For example:

    SDL2_ROOT       = C:\dev\SDL2-2.0.7
    SDL2_IMAGE_ROOT = C:\dev\SDL2_image-2.0.2

You should now be able to use the provided Visual Studio Solution.
As I did not provide any *filters* for the solution, you may want to either introduce your own or simply use the *all files* view.

**Note:** While CMake is capable of generating Visual Studio Solutions, I did not use this feature for this project.

### Linux

Install the SDL2 and SDL2_Image libraries using your system package manager.
Be sure to install the development packages which bring along the required headers.

The provided CMake configuration should find and link the required libraries.

## Resource Path

The resulting binary (`roguelike`) expects the `resource` folder to be located in the current working directory (CWD).
Therefore you'd have to run the resulting binary from the project directory rather than the build directory.
For instance:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make -j8
    $ (cd .. && build/roguelike)

For Visual Studio this should work out-of-the-box.

## Encountering Issues

Please talk to your team mates and fellow students before contacting me about issues with the build process.
By now you should be able to setup things yourself.
If no solution arises feel free to send me an email using the link in the main README.
