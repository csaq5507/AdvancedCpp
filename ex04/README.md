# Exercise Sheet 4 -- Brave New Worlds

*due on 10 November 2017*

In this exercise sheet (and a few of the following ones) you will build a basic dungeon crawler.
If you are not familiar with this genre of video games, read up on it and play a few rounds of [nethack] to get your feet wet.

[nethack]: https://en.wikipedia.org/wiki/NetHack

## Task 1

In the provided folder `roguelike` you will find some code which should get you started.
You are free to change whatever you like.
Make yourself familiar with the provided code and setup your development environment.
Detailed information is provided in [`roguelike.md`](roguelike.md).
Try to understand the ownership and lifetime of each instance and how components integrate with each other.

After examining the code, write down what your modifications are and the reasoning behind them (plain text file).

Do not introduce any new dependencies to the dungeon crawler project, stick with:

- C++ standard library (C++14 standard)
- C standard library (as fallback)
- Boost (not yet used)
- [SDL2], with additional components like [SDL2_Image]

[SDL2]: https://www.libsdl.org/download-2.0.php
[SDL2_Image]: https://www.libsdl.org/projects/SDL_image/

## Task 2

Your first real task is to create the game world (ie terrain) itself as well as scrolling the view.
We also required collision to prevent the player from moving *out of bounds*.

Get or build yourself a sprite set for the terrain.
It should include at least one sprite for the (walkable) floor and one for (non-walkable) walls.

Build a data structure representing a single map of your game.
Maps themselves should be handled as resource files which can be loaded, similar to sprite sets.
Choose / define a proper file-format for your maps.

Connect your data structure with the game so that the terrain of your map is rendered.

Provide at least one map which is larger than what the view can see, so we can test the scrolling of the view later on.

Implement scrolling of the view.
Of course the view should follow the player.

Your maps should not allow the player to move *out of bounds*.
Therefore you have to place walls and implement collision so that entities can only walk on the floor, but not walls.

## Task 3

Pick a game mechanic typically found in dungeon crawlers.
Write a specification (plain text file, no fancy LaTeX or Word) describing the game mechanic and how to implement it given your current code base.
Imagine someone else has to implement it based solely on your specification.

Implement the chosen game mechanic.

In case you are clueless on what to choose, here are a few examples:

- inventory system
- dialogue system
- basic combat (melee / ranged)
- casting spells
- conditions (on fire, chilled, entangled, ...)
- basic interaction with the game world (doors, switches, pressure plates, ...)
- basic monsters with AI (move along a fixed path, move towards the player, ...)
- ...

## Task 4

Same as task 3, but choose a different game mechanic.

- - -

## Submission

Each **team** (not each person):
Take the 3 text files you created in this exercise sheet (changes to the code base and specifications of game mechanics) and send them to me using the link below.

Please try to meet the following criteria:

- content is properly formatted
    - well structured
    - lines do not exceed 80 columns
    - paragraphs are clearly separated
    - headings are clearly visible
    - lines do not contain trailing white-space
- files are UTF-8 encoded and use Unix line-endings (`\n`)
- files contain *one* newline at the end
- files are *self-contained* (ie no references to other files like images or so)
- files may contain *ASCII art* (not restricted to ASCII, UTF-8 characters are okay)
- files are named as follows (where `XX` is the team number, 2 digits, leading zero, ex: `07`)
    - `team_XX_changes.txt`
    - `team_XX_mechanic_1.txt`
    - `team_XX_mechanic_2.txt`

:email: [send email](mailto:alexander.hirsch@uibk.ac.at?subject=703807%20-%20Dungeon%20Crawler%201)

**Unrelated Side Note:** If you have never heard about the [Phrack Magazine], pay them a visit and browse through their plain text papers.
They are mostly security related and of no importance to this lab.
I just wanted to show you how plain text content can convey a lot of information.

[Phrack Magazine]: http://www.phrack.org/

- - -

![The Pursuer](../gfx/the_pursuer.jpg)

> The Pursuers may have been knights who were cursed.
> Like Paladin Leeroy, they were given a mission to atone for their sins; to hunt down and kill all other bearers of the darksign which indicates they are cursed.
> They may have been convinced that this would cure them of their own curse and therefore symbolically atone for their sins.
> What we know for sure is that the Pursuer hunts those who are Undead.
> It has a large quiver on its back that carries an array of weapons, presumably taken from Undead like us who were defeated.

> They may have been a part of a kingdom we know about, we can’t be sure.
> It is possible they were warriors of Alken.
> The Ring of Blades can only be gained by defeating the Pursuers scattered across Drangleic and its text indicates it was made in Alken.
