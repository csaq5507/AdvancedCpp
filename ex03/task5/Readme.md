# Warnings

Compiling with gcc -o bubble_sort -O0 -g -std=c99 -Wall -Wextra bubble_sort.c
leads to no warnings.

# Debuggig result

Debugging done with visual studio 2017.
Imideatly showed that the value of sizeof(array) is 256 on my machine,
which is the size in bytes. This can yield to a index out of bounds in the
following for loop:

    for (unsigned i = 0; i < rand() % sizeof(array); i++) {
        array[i] = rand();
    }

If rand() % 256 is at least 32 times over the value of i at current iteration.
Example rand() = constant = 255
This means at the 32-th iteration we start to corrupt our stack.

