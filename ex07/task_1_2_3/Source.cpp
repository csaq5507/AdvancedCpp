#include "MyVector.h"
#include "BiLinkedList.h"
#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
void printElem(T i) {
	std::cout << i << " ";
}

int main(void) {
	MyVector<int> test;
	MyBidirecListNode<int> testList{ 2 };

	auto iter = testList.begin();
	{
		MyVector<int> tmp;
		int size = 15;
		for (int i = 0; i < size; i++) {
			tmp.push_back(i);
			testList.push_front(i);
		}
		test = tmp;
	}
	std::for_each(test.begin(), test.end(), printElem<int>);
	std::cout << std::endl;


	for (auto it = testList.begin(); it != testList.end(); ++it) {
		std::cout << (*it).GetVal() << " ";
	}

	std::for_each(testList.begin(), testList.end(), [](MyBidirecListNode<int>& v) -> void {	std::cout << v.GetVal() << " ";});
	std::cout << std::endl;

	std::getchar();
}