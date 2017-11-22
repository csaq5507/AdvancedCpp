#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>

constexpr int numOfVectorElements = 10;
constexpr int modulo = 4;
void print(int n) {
	std::cout << n << ";";
}
template <typename T>
void printFindResult(T findIter, T endIter) {
	if (findIter == endIter) {
		std::cout << "not found" << std::endl;
	}
	else {
		std::cout << std::to_string(*findIter) << std::endl;
	}
}

bool pred(int n) {
	return n < modulo;
}

int main(void) {

	std::vector<int> vec;
	std::vector<int> copyVec;
	for (int i = 0; i < numOfVectorElements; i++) {
		vec.push_back(i % modulo + 1); //this allows to have some duplicates which will present the results of some methods of the list give in task 3
	}

	//for each applies function to all elements e.g. map in functional language
	std::cout << "Use of for_each to print all values" << std::endl;
	std::for_each(vec.begin(), vec.end(), print);
	std::cout << std::endl;

	//find as the name suggest searches for the element and returns the iterator to this element or iterator point to the end
	auto it = std::find(vec.begin(), vec.end(), modulo + 1);
	std::cout << "print find result of " << std::to_string(modulo + 1) << std::endl;
	printFindResult(it, vec.end());

	std::cout << "print find_if result" << std::endl;
	it = std::find_if(vec.begin(), vec.end(), [](int n) -> bool {return n < modulo;});
	printFindResult(it, vec.end());

	std::copy(vec.begin(), vec.end(), std::back_inserter(copyVec));

	std::cout << "print equal result of copied vector result" << std::endl;
	std::cout << std::equal(vec.begin(), vec.end(), copyVec.begin()) << std::endl;

	std::cout << "Apply a map with function (*2) on all elements of the vector" << std::endl;
	std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) -> int {return x * 2;});
	std::for_each(vec.begin(), vec.end(), print);
	std::cout << std::endl;

	//unique makes sense in sorted array
	std::cout << "Call unique on the sorted copied vector from before" << std::endl;
	std::sort(copyVec.begin(), copyVec.end());
	auto logicalEnd = std::unique(copyVec.begin(), copyVec.end());
	copyVec.erase(logicalEnd, copyVec.end());
	std::for_each(copyVec.begin(), copyVec.end(), print);
	std::cout << std::endl;


	std::cout << "Partition the vector" << std::endl;
	auto partIt = std::partition(vec.begin(), vec.end(), [](int e) -> bool {return e == modulo;});
	std::for_each(vec.begin(), partIt, print);
	std::cout << std::endl;
	std::for_each(partIt, vec.end(), print);
	std::cout << std::endl;


	//ower_bound / upper_bound makes sense in sorted array
	std::cout << "Sort vector and print values in range of upper and lower bound" << std::endl;
	vec.push_back(3);
	copyVec.push_back(3);
	std::sort(vec.begin(), vec.end());

	auto lower = std::lower_bound(vec.begin(), vec.end(), 2);
	auto upper = std::upper_bound(vec.begin(), vec.end(), modulo + 1);

	std::for_each(lower, upper, print);
	std::cout << std::endl;


	std::vector<int> unionVec;
	std::cout << "A := { ";
	std::for_each(vec.begin(), vec.end(), print);
	std::cout << "}" << std::endl;
	std::cout << "B := { ";
	std::for_each(copyVec.begin(), copyVec.end(), print);
	std::cout << "}" << std::endl;
	/* Behaviour explained in cpp reference:
	If some element is found m times in [first1, last1) and n times in [first2, last2), then all m elements will be copied from [first1, last1)
	to d_first, preserving order, and then exactly std::max(n-m, 0) elements will be copied from [first2, last2) to d_first, also preserving order.
	*/
	std::set_union(vec.begin(), vec.end(), copyVec.begin(), copyVec.end(), std::back_inserter(unionVec));
	std::cout << "A union B" << std::endl;
	std::for_each(unionVec.begin(), unionVec.end(), print);
	std::cout << std::endl;

	std::cout << "Accumulate union vector" << std::endl;
	auto res = std::accumulate(unionVec.begin(), unionVec.end(), 0);
	std::cout << std::to_string(res) << std::endl;
	std::cin.get();

}