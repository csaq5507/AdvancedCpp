# Exercise Sheet 2 -- First Challenge

*due on 27 October 2017*

In this exercise sheet you are given the task of creating a trimmed down version control system (VCS) similar to [Git] or [Mercurial].
One of the reasons for assigning you this task is to test your development setup.
Another is to force you into exploring the C++ language for yourself.

[Git]: https://git-scm.com/
[Mercurial]: https://www.mercurial-scm.org/

As C++ is a very complex language, and because there is a lot of out-dated (or plain wrong) information on the web, you will probably make mistakes along the way.
Do not worry -- your implementation does not have to be perfect.
But if errors occur, you should investigate and understand them prior to fixing them.

Please read the whole exercise sheet before starting with the task at hand.

## Task 1

You are to implement a VCS with the following capabilities:

- The user interacts with your VCS via a *single* executable.
- **Initialise** a folder in such a way that it can be used for version control.
- **Commit** changes.
- **Checkout** a previous commit.
- Create new commits when a previous commit has been checked out, yielding a new **branch**.
- **Show** a commit.
- Display the relationship between commits as **graph**.
- **Merging** two branches.

The file [`SPECIFICATION.md`](SPECIFICATION.md) elaborates these bullets in more detail.
Furthermore, your implementation is only allowed to use:

- C++ standard library (C++14 standard)
- Boost library
- C standard library (as fallback)
- `diff` command
- `patch` command

## Task 2

Setup a way to test your implementation in the form of unit- and integration-tests.

- Think about which components of your implementation are critical or error prone.
- Write some tests for these components (unit-tests).
- Write some more tests which check the interaction between multiple components.

## Task 3

Similar to Task 2, setup a way to benchmark your implementation.

- Think about which metrics are interesting for benchmarks.
- Think about which components form bottlenecks.
- Create 3 different benchmarks for your implementation.

## Task 4

Throughout your implementation, document your errors and pitfalls.
Think about ways to prevent yourself from doing the same mistakes again in future.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

![Iudex Gundyr](../gfx/iudex_gundyr.jpg)

> Gundyr, corrupted by the abyss, spends eternity testing unkindled to see if they are worthy to Link the Flame.
> He was once an unkindled himself but arose too late to fulfill his duty, never meeting his Fire Keeper, who had been buried within the tower behind Firelink Shrine with the Estus Ring.
> The flame had already gone out and the bells failed to ring which started a new dark age.
