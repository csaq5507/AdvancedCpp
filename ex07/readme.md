# Exercise Sheet 7 -- Extending your Toolbox

*due on 1 December 2017*

## Task 1

Implement your own version of `std::vector` without using any of the provided containers -- use *regular arrays* (`new[]` / `delete[]`) to house your elements.
The focus of this task lies on the use of templates.
You do not have to concern your self with custom allocators and iterators (see task 2).

Test your implementation with different types (`int`, `double` and a custom structure).

## Task 2

Take your vector from task 1 and implement iterators.
You might want to read through the documentation of iterators to get to know the different kinds of iterators and how they work.

Write some tests utilising algorithms provided by the standard library to check if your iterators behave like they should.

## Task 3

Same as task 1 and 2, but instead of mimicking `std::vector`, now create a doubly linked list.
For this task, focus on the iterator part, as the template related stuff will be quite similar.

## Task 4 (No Points to Score)

Refactor your dungeon crawler.

- - -

![Deacons of the Deep](../gfx/deacons_of_the_deep.jpg)

> The Deacons of the Deep are led by Archdeacon Royce, one of Aldrich's most devoted followers, alongside McDonnell and Klimt.
> It is mentioned that Klimt attended to Rosaria, whom he deemed as a goddess, and one day lost his faith, but the sequence of events and their causes are not certain, and whether or not he is still alive is difficult to figure.

> When Aldrich and McDonnell traveled to Irithyll with a small group of deacons to meet with Pontiff Sulyvahn, Royce and the other deacons stayed to guard their lord's empty coffin from intruders, in the hopes that he would one day return.
> It is said that McDonnell imparted the spell Deep Soul to Royce and his followers, to aid them in their defense.
