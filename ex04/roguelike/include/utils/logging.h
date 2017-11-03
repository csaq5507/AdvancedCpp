#ifndef ROGUELIKE_UTILS_LOGGING_H_
#define ROGUELIKE_UTILS_LOGGING_H_

#include <cstdio>
#include <cstdlib>

#define INFO(s_, ...) printf("[Info]    " s_ "\n", ##__VA_ARGS__)

#define WARN(s_, ...) printf("[Warning] " s_ "\n", ##__VA_ARGS__)

#define ERROR(s_, ...) printf("[Error]   " s_ "\n", ##__VA_ARGS__)

#define FATAL(s_, ...)        \
    ERROR(s_, ##__VA_ARGS__); \
    std::exit(EXIT_FAILURE)

#endif  // ROGUELIKE_UTILS_LOGGING_H_
