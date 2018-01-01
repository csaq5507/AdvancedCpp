#ifndef ROGUELIKE_UTILS_VEC_H_
#define ROGUELIKE_UTILS_VEC_H_

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
    std::array<int, N> _data;

public:

    Vec(): _data() {
        for (int i = 0; i < N; ++i) {
            _data[i] = 0;
        }
    }

    template<typename...T2, typename std::enable_if<sizeof...(T2) == N - 1, int>::type = 0>
    Vec(int first, T2 ...args) : _data()
    {
        _data[0]=first;
        std::vector init({args...});
        for (int i = 1; i < N; ++i) {
            _data[i] = init[i-1];
        }
    }

    int& operator[] (const int index)
    {
        return _data[index];
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

    friend std::ostream& operator<<(std::ostream& os, const Vec& dt)
    {
        os << std::string(dt);
        return os;
    }
};



#endif  // ROGUELIKE_UTILS_VEC_H_
