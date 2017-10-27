//
// Created by ivan on 27/10/17.
//

#include "my_unique_ptr.h"

int main(int argc, char * argv[])
{
    my_unique_ptr a(new Vec3());
    my_unique_ptr b = a;
}