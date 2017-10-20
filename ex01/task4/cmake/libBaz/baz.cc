#include "baz.h"

#include <iostream>

#include "bar.h"

void baz() {
    bar();
    std::cout << "Function baz called" << std::endl;
}
