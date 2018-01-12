#ifndef ROGUELIKE_UTILS_VEC2_H_
#define ROGUELIKE_UTILS_VEC2_H_

#include <ostream>
#include <string>
#include <array>
#include <cstdarg>
#include <initializer_list>
#include <algorithm>
#include <type_traits>
#include <tuple>
#include <vector>
#include <numeric> // for std::accumulate
#include <sstream>

template <unsigned N>
class Vec {

private:
    std::array<int, N> _data = std::array<int, N>();


public:

    int &x;
    int &y;

    Vec(): x(_data[0]), y(_data[1]){
        for (int i = 0; i < N; ++i) {
            _data[i] = 0;
        }
    }

    template<typename...T2, typename std::enable_if<sizeof...(T2) == N - 1, int>::type = 0>
    Vec(int first, T2 ...args): x(_data[0]),y(_data[1])

    {
        _data[0]=first;
        std::vector init({args...});
        for (int i = 1; i < N; ++i) {
            _data[i] = init[i-1];
        }
    }

    Vec(const Vec<N>& other): x(_data[0]), y(_data[1])
    {
        for (int i = 0; i < N; ++i) {
            _data[i] = other._data[i];
        }
    }

    int& operator[] (const int index)
    {
        return _data[index];
    }

    Vec<N> operator+(const Vec<N>& rhs) const {
        Vec<N> temp = Vec<N>();
        for (int i = 0; i < N; ++i) {
            temp._data[i] = this->_data[i] + rhs._data[i];
        }
        return temp;
    }

    Vec<N> &operator+=(const Vec<N> &rhs) {
        for (int i = 0; i < N; ++i) {
            this->_data[i] += rhs._data[i];
        }
        return *this;
    }

    Vec<N> &operator=(const Vec<N> &rhs) {
        for (int i = 0; i < N; ++i) {
            this->_data[i] = rhs._data[i];
        }
        return *this;
    }

    bool operator==(const Vec<N> &other) const {
        for (int i = 0; i < N; ++i) {
            if (this->_data[i] != other._data[i])
                return false;
        }
        return true;
    }

    operator std::string() const
    {

        std::ostringstream oss;
        oss << "Vec" << N << "(" << _data[0];
        for (int i = 1; i < N; ++i) {
            oss<<", "<<_data[i];
        }
        oss<<")";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec<N>& dt)
    {
        os << std::string(dt);
        return os;
    }
};


using Vec2 = Vec<2>;

#endif  // ROGUELIKE_UTILS_VEC2_H_
