#ifndef ROGUELIKE_UTILS_VEC2_H_
#define ROGUELIKE_UTILS_VEC2_H_

#include <ostream>
#include <string>

class Vec2 {
  public:
    int x;
    int y;

    Vec2();

    Vec2(int x, int y);

    Vec2& operator+=(const Vec2& rhs);
};

std::string to_string(const Vec2& v);

std::ostream& operator<<(std::ostream& stream, const Vec2& v);

#endif  // ROGUELIKE_UTILS_VEC2_H_
