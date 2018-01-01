//
// Created by ivan on 01/01/18.
//
#include "task1/vec.h"
#include <iostream>

int main(int args, char * argv[])
{
    Vec<2> a=Vec<2>();
    Vec<3> b(1,2,3);
    Vec<4> c(1,2,3,4);
    std::cout<<a<<std::endl<<b<<std::endl<<c<<std::endl;
    std::cout<<a.x<<std::endl<<b.z;
}