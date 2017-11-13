#include <iostream>
#include "Person.h"
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace foo;

template <typename T>
void PrintVector(std::vector<T> v) {
	for (auto& e : v)
	{
		std::cout << e << " || ";
	}
}

int main(char** argv, int argc) {

	std::cout << foo::Person{ "John", "Smith", 42 } << std::endl;


	Person p1 = Person("a", "b", 1);
	Person p7 = Person("a", "b", 1);
	Person p10 = Person("a", "b", 2);
	Person p2 = Person("c", "b", 2);
	Person p3 = Person("d", "e", 4);
	Person p4 = Person("w", "e", 5);
	Person p5 = Person("n", "m", 6);
	Person p6 = Person("h", "p", 9);
	Person p8 = Person("s", "e", 8);
	Person p9 = Person("u", "v", 5);

	std::cout << foo::Person{ "John", "Smith", 42 } << std::endl;
	std::cout << "Creating vector" << std::endl;
	//the vector does not call any operators
	std::vector<Person> v1{ p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 };
	std::cout << "done creating vector" << std::endl;

	std::cout << "Creating set" << std::endl;
	//the set calles the < operator, cpp-reference:: a and b are equal iff !comp(a, b) && !comp(b, a)
	std::set<Person> s1{ p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 };
	std::cout << "done creating set" << std::endl;
	
	std::cout << "Sort by first name" << std::endl;
	std::sort(v1.begin(), v1.end(), &Person::compFirstName);
	PrintVector(v1);
	std::cout << std::endl;

	std::cout << "Sort by last name" << std::endl;
	std::sort(v1.begin(), v1.end(), &Person::compLastName);
	PrintVector(v1);
	std::cout << std::endl;

	std::cout << "Sort by age" << std::endl;
	std::sort(v1.begin(), v1.end(), &Person::compAge);
	PrintVector(v1);
	std::cout << std::endl;

	//using a hash map
	std::unordered_map<Person, int, MyHash> hashMap;
	hashMap.insert(std::make_pair(p1, 1));
	hashMap.insert(std::make_pair(p2, 2));
	std::cin.get();
}