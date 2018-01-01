# Exercise Sheet 9 -- Meta

*due on 12 January 2018*

## Task 1

In the code originally provided for the dungeon crawler project, a class `Vec2` was provided to model a vector in 2D space.
Your task is to create a class template in the same manner for *N*-dimensional vectors.

Store the elements of your vector in a (private) `std::array<int, N>` named `data`.
Implement the same operations as the `Vec2` class in your dungeon crawler project has.
The following should be among them:

- default constructor initialising everything to `0`
- constructor taking *N* `int`s
- accessing elements via the subscript operator `[]`
- `to_string` overload
- output stream operator overload

Write some unit-tests to verify the correctness of your implementation.
Pay attention to provide a well defined interface, for instance:
An instantiation of your template class with *N = 2* should not have a constructor taking *one* `int` or *three* `int`s.

## Task 2

Take the template class from task 1.
Even though you have added the same functionality you may not be able to simply replace the `Vec2` of your dungeon crawler with an instantiation of your new template class with *N = 2*.
The problem is that (originally) the `Vec2` stores its elements as members `x` and `y`.

From task 1 you should have a *generic* vector template which can be instantiated for an arbitrary number of dimensions.
Yet, when *N = 2* the elements should also be accessible through `.x` and `.y`.
Similar for *N = 3*: `.x`, `.y`, `.z.`.

Try to find an elegant solution and think about its benefits and downsides.

You should now be able to replace your dungeon crawlers `Vec2` implementation with your template class:

```cpp
using Vec2 = Vec<2>;
```

*Hint:* Creating a class hierarchy is allowed. Although, think about automatic conversion from derived to base classes.

## Task 3

Revisit the meta programming example from the lecture regarding `std::tuple`.

Given the following class template:

```cpp
template <typename... Types>
class type_set {};
```

`type_set` should behave like a set of types.
The empty set would therefore be `type_set<>`, while the set containing the type `int` would be `type_set<int>`, so on and so forth.

- Create a meta function `type_set_contains_v` which checks if a given `type_set` contains a given type.
- Create a meta function `type_set_is_subset_v` which checks if a given `type_set` is a subset of another given `type_set`.
- Create a meta function `type_set_is_same_v` which checks if a given `type_set` is equal to another given `type_set`.
- (Bonus) Create a meta function `type_set_size_v` which tells the size of a given `type_set`.
  For `type_set<int, int, float>` it should return 2.

Try not to use any of the utilities provided by the standard library (like the example provided in the lecture).

*Hint:* If you are struggling with this exercise you might want to have a look at how *fold* (ie *reduce*) is used in functional programming languages.

## Task 4

Create game content for your dungeon crawler.
Do not worry about new mechanics or features, simply build content based on what mechanics / features are already present and working.

The goal is to have more content for your player to play through.

A different way of solving this exercise would be to build generators (similar to the random map generation).

- - -

![Abyss Watcher](../gfx/abyss_watcher.jpg)

> The Abyss Watchers were the main component of the Undead Legion of Farron, a special fighting force formed to combat the threat of the Abyss.
> Taking inspiration from the Wolf Knight (Sir Artorias, the Abyss Walker), the Abyss Watchers themselves sought to utilize the techniques of Artorias, and partook of wolf blood to do so.
> Now equipped with the strength of Artorias, they became intensely strong and agile, fighting in a coordinated and sporadic pack akin to wolves.
