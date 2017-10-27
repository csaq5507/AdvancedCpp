#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(long *array) {
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (int i = 0; i < 31; i++) {
            long *item_one = &array[i];
            long *item_two = &array[i + 1];

            if (*item_one <= *item_two) {
                continue;
            }

            sorted = false;

            long swap_store = *item_two;
            *item_two = *item_one;
            *item_one = swap_store;
        }
    }
}

void do_stuff(void) {
    long array[32];

    srand(time(NULL));

    for (unsigned i = 0; i < rand() % sizeof(array); i++) {
        array[i] = rand();
    }

    sort(array);
}

int main(void) {
    do_stuff();
    return EXIT_SUCCESS;
}
