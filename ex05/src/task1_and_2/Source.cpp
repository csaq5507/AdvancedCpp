#include <iostream>
#include "../Person.h"
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
	std::cout<<std::endl;

}

template <typename T>
void PrintSet(std::set<T> * v) {
	for (auto& e : *v)
	{
		std::cout << e << " || ";
	}
	std::cout<<std::endl;
}

int main(char** argv, int argc) {



	std::cout << foo::Person{ "John", "Smith", 42 } << std::endl;


	Person p0 = Person("0", "0", 0);
	Person p1 = Person("1", "1", 1);
	Person p2 = Person("2", "2", 2);
	Person p3 = Person("3", "3", 3);
	Person p4 = Person("4", "4", 4);
	Person p5 = Person("5", "5", 5);
	Person p6 = Person("6", "6", 6);
	Person p7 = Person("7", "7", 7);
	Person p8 = Person("8", "8", 8);
	Person p9 = Person("9", "9", 9);

	std::cout << "Creating vector" << std::endl;
	//the vector does not call any operators
	std::vector<Person> v1{ p9, p8, p7, p6, p5, p4, p3, p2, p1 ,p0 };
	std::cout << "done creating vector" << std::endl;

	std::cout << "Creating set" << std::endl;
	//the set calles the < operator, cpp-reference:: a and b are equal iff !comp(a, b) && !comp(b, a)
	std::set<Person> s1{ p9, p8, p7, p6, p5, p4, p3, p2, p1 ,p0 };
	std::cout << "done creating set" << std::endl;

	std::cout << "Print Set: " << std::endl;
	PrintSet(&s1);

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
}