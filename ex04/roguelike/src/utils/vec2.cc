#include "utils/vec2.h"

Vec2::Vec2() : Vec2(0, 0){};

Vec2::Vec2(int x, int y) : x(x), y(y) {}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2({this->x+rhs.x, this->y+rhs.y});
}

bool Vec2::operator==(const Vec2& other) const {
    return this->x==other.x && this->y==other.y;
}

std::string to_string(const Vec2& v) {
    std::string s{"Vec2{"};
    s += std::to_string(v.x);
    s += ",";
    s += std::to_string(v.y);
    s += "}";
    return s;
}

std::ostream& operator<<(std::ostream& stream, const Vec2& v) {
    return stream << to_string(v);
}
