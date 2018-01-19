//
// Created by ivan on 10/11/17.
//

#include <chrono>
#include "utils/random.h"

unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

std::default_random_engine rnd (seed1);


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