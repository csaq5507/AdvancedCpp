# Exercise Sheet 3 -- Back to Basics

*due on 3 November 2017*

# Task 1

This task focuses on the correct implementation of RAII as well as copy and move semantics.
You are asked to implement the concept of `unique_ptr` and `shared_ptr`.
Since we won't concern ourselves with templates for the moment your implementation will *own* an instance of the following `struct`.

```cpp
struct Vec3 {
    int x, y, z;
};
```

- read the documentation regarding *smart pointers*, `unique_ptr`, and `shared_ptr`
- implement your version of `unique_ptr_to_vec3` and `shared_ptr_to_vec3` fulfilling these requirements:
    - *dynamically* allocate an instance of `Vec3` in your constructor (initialise `x`, `y`, `z` to `0`)
    - deallocate the `Vec3` instance in your destructor
    - implement correct copy semantics (copy constructor / copy assignment)
    - implement correct move semantics (move constructor / move assignment)
    - enable access to `Vec3` via the operators `*` and `->`
    - thread-safety for `share_ptr_to_vec3`'s reference counter is not required
- provide unit tests for your implementation
    - pay attention to corner-cases like self-assignment (`v = v`)
- check your implementation for memory leaks using `valgrind`

# Task 2

Let us now investigate the problem of *invalidated* references.
For this task you are okay to ignore compiler warnings.

- write a function which returns a *pointer* to one of its local variables
- write a function which returns a *reference* to one of its local variables
- compile with different compilers, optimisation enabled (for Clang and GCC you may want to pass `-fno-stack-protector`)
- run each resulting executable and observe their behaviour
- examine the generated assembly code for both functions and compare differences between compilers
- read up on the topic of *calling conventions* and explain your findings

# Task 3

Examine the program `iterations.cc` and think about the expected output.
Compile the program and run it.
What do you notice?
Did you expect this behaviour?
Did you get any compiler warnings?
Investigate what is actually happening (consider using a debugger).

How can such errors be prevented?
Look for tools (ex: static code analysers) which help discovering such faulty code.

**Note 1:** If you run the executable and everything seems normal, try changing the initial content of `xs`, using different optimisation flags, or a different compiler.
The actual behaviour of this executable depends on a lot of system-related factors.

**Note 2:** If you are not that familiar with using a debugger, consider doing task 5 before this one.

# Task 4

You are given the program `strange.cc`.
Compile it with different compilers and optimisation flags.
What do you notice?
What is really happening here?

# Task 5 (Bonus)

Make yourself comfortable with GDB. Take `bubble_sort.c` and compile it:

    $ gcc -o bubble_sort -O0 -g -std=c99 -Wall -Wextra bubble_sort.c

Do you receive any warnings when the file gets compiled?
Run the executable in a loop -- it should *segfault* momentarily.

    $ while ./bubble_sort; do echo ok; done

Debug the executable with GDB and figure out what is happening.
Try using GDB's *reverse-debugging-capabilities*, *watching* memory locations, and the ability to attach commands to a breakpoint.

**Note:** Similar to task 3, the behaviour of the executable depends on different factors.
If the executable does not crash after a minute or so, try changing optimisation flags and passing either `-fno-stack-protector` or `-fstack-protector`.

- - -

![Dragon Rider](../gfx/dragon_rider.jpg)

> The Dragonriders used to serve in King Vendrick's royal guard long ago.
> These riders mounted wyverns and caused chaos on the battlefield due to their unparalleled strength.
> The rank of Dragonrider was reserved for honorable warriors who helped found Drangleic.
> Together with the King, they crushed the land's former inhabitants and erected a magnificent kingdom upon their graves.

> Those wishing to join the ranks of the Dragonriders were forced to undergo intense and dangerous training.
> Only those who passed the training were allowed in the order, those who failed would be ripped apart by the very mounts they tried to command.
