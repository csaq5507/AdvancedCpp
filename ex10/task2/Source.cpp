#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include "Factorial.h"

struct A {};
struct B {
	void print_to(std::ostream& o) {
		o << "B\n";
	}
};

struct C {
	friend std::ostream& operator<<(std::ostream& o, C);
};

std::ostream& operator<<(std::ostream& o, C) {
	return o << "C\n";
}

struct D {
	friend std::ostream& operator<<(std::ostream& o, D);
	void print_to(std::ostream& o) {
		o << "D\n";
	}
};

std::ostream& operator<<(std::ostream& o, D) {
	return o << "D\n";
}

template<typename T, class = void>
struct has_print_to : public std::false_type {};

template<typename T>
struct has_print_to<T,
	std::void_t<decltype(std::declval<T>().print_to(std::declval<std::ostream&>()))>
> : public std::true_type {};

template<typename T, class = void>
struct has_output_stream : public std::false_type {};

template<typename T>
struct has_output_stream<T,
	std::void_t<decltype(operator<<(std::declval<std::ostream&>(), std::declval<T>()))>
> : public std::true_type {};

template<typename T>
constexpr bool has_print_to_v = has_print_to<T>::value;

template<typename T>
constexpr bool has_output_stream_v = has_output_stream<T>::value;

// now we can write our template
template<typename T>
constexpr bool is_printable = has_print_to_v<T> || has_output_stream_v<T>;

int main() {

	int f = Factorial<20>();
	int s = Ackerman<3, 5>::value;
	//ackerman recusrive calls grow too fast
	//int s1 = Ackerman<4, 3>::value;
	//the following function increased the needed RAM of MSVS 17 from 170MB to 1GB+ till compiler out of heap space error appeared
	//and needs more than a min to compile
	//auto squirtRes = Sqrt<200000>::value;

	//works fine and fast
	auto optimizedSquirtRes = OptSqrt<200000>::value;
	std::cout << f << std::endl;
	std::cout << s << std::endl;
	std::cout << optimizedSquirtRes << std::endl;
}