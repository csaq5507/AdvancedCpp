//
// Created by ivan on 12/01/18.
//
#include <iostream>
#include <type_traits>


struct A {
    void print_to(std::ostream& o) {
        o << "A\n";
    }
};
struct B {

};
std::ostream& operator<<(std::ostream& o, B) {
    return o << "B\n";
}
struct C {

};
struct D {
    void print_to(std::ostream& o) {
        o << "D\n";
    }
};
std::ostream& operator<<(std::ostream& o, D) {
    return o << "D\n";
}




////////////////////////////////////
template<typename T, class=void>
struct has_print_to : public std::false_type {};

template<typename T>
struct has_print_to<T, std::void_t< decltype(std::declval<T>().print_to(std::declval<std::ostream&>()) ) >
> : public std::true_type {};

template<typename T, class=void>
struct has_print_stream : public std::false_type {};

template<typename T>
struct has_print_stream<T, std::void_t<decltype(std::cout<<std::declval<T>() ) >
> : public std::true_type {};

template<typename T>
constexpr bool is_printable_v = has_print_to<T>::value || has_print_stream<T>::value;

// now we can write our template

template<typename T>
std::enable_if_t<is_printable_v<T> > dump(T t) {
    std::cout<<"Is printable"<<std::endl;
}
template<typename T>
std::enable_if_t<!is_printable_v<T> > dump(T t) {
    std::cout<<"Is not printable"<<std::endl;
}


int main() {
    A a;
    B b;
    C c;
    dump<A>(a);
    dump<B>(b);
    dump<C>(c);


}
