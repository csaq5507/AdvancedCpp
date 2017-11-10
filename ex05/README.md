# Exercise Sheet 5 -- Taking Inventory

*due on 17 November 2017*

## Task 1

Create a class `Person` containing the following fields:

- `std::string first_name`
- `std::string last_name`
- `int age`

The fields should be private and you should provide getter, setter, and a constructor setting all 3 fields to a given value.

- Implement relational and comparison operators:
  `==`, `!=`, `<`, `<=`, `>`, and `>=`.
- Implement the operator `<<` for `std::ostream`, so we can write:

      std::cout << Person{"John", "Smith", 42} << std::endl;

- For primitive types a function `std::to_string` is provided in the standard library.
  Implement a similar function `to_string` for `Person`.

Justify whether your function / operator is a regular member function, static member function, friend function, or regular function.

- Put your whole implementation (including `to_string`) in a namespace (eg `foo`).

Explain why this is possible without `using namespace foo`:

    foo::Person p1{"John", "Smith", 42};
    std::cout << to_string(p1) << std::endl;

## Task 2

Use your `Person` class from task 1, instantiate it 10 times with different parameters.
Put all 10 instanced in a `std::vector` and also in a `std::set`.
Investigate which operators are used by each container.

Since the order you defined on your `Person` class may not suit every possible application, provide comparison functions for each of the 3 fields.
For each comparison function, call `std::sort` on your `std::vector` and observe the result.

There are also containers available which utilise hash functions.
Implement the missing pieces for `Person` so that it can be stored in one of the containers utilising hash functions.
Provide an example.

## Task 3

The C++ standard library comes with a lot of different algorithms which can be used in conjunction with the provided containers.
Read through [the list](http://en.cppreference.com/w/cpp/algorithm) and provide an example for each of the following:

- `for_each`
- `find`
- `find_if`
- `copy`
- `transform`
- `unique`
- `parition`
- `lower_bound` or `upper_bound`
- `set_union` on `std::vector`
- `accumulate` with custom binary operator

## Task 4

Spend some more time on your dungeon crawler.
Do some polishing, refactoring, or try out something new.

- - -

![Bonfire](../gfx/bonfire.jpg)
