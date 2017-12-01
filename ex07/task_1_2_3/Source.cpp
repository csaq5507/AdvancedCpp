#include "MyVector.h"
#include "BiLinkedList.h"
#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
void printElem(T i) {
	std::cout << i << " ";
}

class foo
{
public:
	double a;
	foo() : a(0) {}
	foo(double c) : a(c) {}
	~foo(){}

};
class bar
{
public:
	std::string a;
	bar() : a(" ") {}
	bar(std::string c) : a(c) {}
	~bar(){}

};

int main(void) {
	MyVector<foo> lol;
	lol.push_back(foo(3));
	for (auto it = lol.begin(); it != lol.end(); ++it) {
		std::cout << (*it).a << " ";
	}
	std::cout << std::endl;
	MyVector<bar> lol2;
	lol2.push_back(bar("hi"));
	for (auto it = lol2.begin(); it != lol2.end(); ++it) {
		std::cout << (*it).a << " ";
	}
	std::cout << std::endl;
	MyVector<int> test;
	MyBidirecListNode<int> testList{ 2 };
	MyBidirecListNode<int> testList2{ 2 };

	auto iter = testList.begin();
	{
		MyVector<int> tmp;
		int size = 15;
		for (int i = 0; i < size; i++) {
			tmp.push_back(i);
			testList.push_front(i);
			testList2.push_back(i);
		}
		test = tmp;
	}
	std::for_each(test.begin(), test.end(), printElem<int>);
	std::cout << std::endl;


	for (auto it = testList.begin(); it != testList.end(); ++it) {
		std::cout << (*it).GetVal() << " ";
	}
	std::cout << std::endl;

	std::for_each(testList.begin(), testList.end(), [](MyBidirecListNode<int>& v) -> void {	std::cout << v.GetVal() << " ";});
	std::cout << std::endl;

	std::for_each(testList2.begin(), testList2.end(), [](MyBidirecListNode<int>& v) -> void {	std::cout << v.GetVal() << " ";});
	std::cout << std::endl;
}