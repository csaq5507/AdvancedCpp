// Example program
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

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

template<typename T>
std::enable_if_t<has_print_to_v<T>> dump(T t) {
	t.print_to(std::cerr);
}
template<typename T>
std::enable_if_t<!has_print_to_v<T>> dump(T t) {
	std::cerr << t;
}


int main() {
	A a;
	B b;
	C c;
	D d;
	
	std::cout << is_printable<A> << std::endl;
	std::cout << is_printable<B> << std::endl;
	std::cout << is_printable<C> << std::endl;
	std::cout << is_printable<D> << std::endl;
}