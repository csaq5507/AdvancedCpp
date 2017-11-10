//
// Created by ivan on 10/11/17.
//

#include "utils/random.h"

std::default_random_engine rnd;


int get_int_random(int from, int to)
{
    std::uniform_int_distribution<int> rng(from, to);
    return rng(rnd);
}

double get_double_random(double from, double to)
{
    std::uniform_real_distribution<double> rng(from, to);
    return rng(rnd);
}