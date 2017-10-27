//
// Created by ivan on 27/10/17.
//
#include <memory>

#include "my_unique_ptr.h"
#include "my_shared_ptr.h"

int main(int argc, char * argv[])
{
    unique_ptr_to_vec3 a;

    std::unique_ptr<int> r;


    my_shared_ptr c(new Vec3());
    my_shared_ptr d = c;
    my_shared_ptr e = d;
    return EXIT_SUCCESS;
}