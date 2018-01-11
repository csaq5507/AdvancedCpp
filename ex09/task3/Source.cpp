#include <iostream>

template <typename T, typename U>
struct Is_same {
	static constexpr bool value = false;
};

template <typename T>
struct Is_same<T, T> {
	static constexpr bool value = true;
};

template<typename T>
constexpr bool Exists() { return false; }

template <typename T, typename First, typename... Types>
constexpr bool Exists() {
	return Is_same<T, First>::value ? true : Exists<T, Types...>();
}

template<typename T>
constexpr int ExistsNumOfTimes() { return 0; }

template <typename T, typename First, typename... Types>
constexpr int ExistsNumOfTimes() {
	return Is_same<T, First>::value ? 1 + ExistsNumOfTimes<T, Types...>() : ExistsNumOfTimes<T, Types...>();
}

template <typename... Types>
struct Type_set {

	template <int BaseVal>
	static constexpr int RemoveDuplicates() {
		return BaseVal;
	}

	template <int BaseVal, typename Arg, typename...Rest>
	static constexpr int RemoveDuplicates() {
		int n = ExistsNumOfTimes<Arg, Arg, Rest...>();
		int sub = n > 1 ? (-1) : 0;
		int res = sub + RemoveDuplicates<BaseVal, Rest...>();
		return res;
	}



	static constexpr int GetNumOfTypes() {
		const int all = sizeof...(Types);
		return RemoveDuplicates<all, Types...>();
	}

	static constexpr int numOfTypes = GetNumOfTypes();

	template <typename T>
	static constexpr bool Type_set_contains_v() {
		return Exists<T, Types...>();
	}

	template <typename SuperSet>
	static constexpr bool Type_set_is_subset_v() {
		return SuperSet::template ContainsAll<Types...>();
	}

	template <typename SuperSet>
	static constexpr bool Type_set_is_same_v() {
		return SuperSet::template ContainsAll<Types...>() && SuperSet::template Type_set_is_subset_v<Type_set<Types...>>();
	}


	template <typename First, typename Sec, typename... T>
	static constexpr bool ContainsAll() {
		return Type_set_contains_v<First>() && ContainsAll<Sec, T...>();
	}

	template <typename First>
	static constexpr bool ContainsAll() {
		return Type_set_contains_v<First>();
	}
};

template <>
struct Type_set<> {
	static const int numOfTypes = 0;

	template <typename SuperSet>
	static constexpr bool Type_set_is_subset_v() {
		return true;
	}

	template <typename SuperSet>
	static constexpr bool Type_set_is_same_v() {
		return SuperSet::numOfTypes == 0;
	}

	template <typename T>
	static constexpr bool Type_set_contains_v() {
		return false;
	}

	static constexpr bool Type_set_contains_v() {
		return true;
	}
};

int main(void) {
	bool isSameTest = Is_same<int, int>::value;
	bool existTest = Exists<int, double, float, void>();
	bool typeSetCont = Type_set<void, int, long>::Type_set_contains_v<double>();
	bool typeSubSetTest = Type_set<int, long, double>::Type_set_is_subset_v<Type_set<int, long, double>>();
	bool typeEqSetTest = Type_set<int>::Type_set_is_same_v<Type_set<int>>();

	std::cout << Type_set<>::numOfTypes << std::endl;
	std::cout << Type_set<int>::numOfTypes << std::endl;
	std::cout << Type_set<double, double, float>::numOfTypes << std::endl;
	std::cout << Type_set<int, double, float, double, int>::numOfTypes << std::endl;

	std::cout << std::endl;
	std::cout << isSameTest << std::endl;
	std::cout << existTest << std::endl;
	std::cout << typeSetCont << std::endl;
	std::cout << typeSubSetTest << std::endl;

	std::cout << typeEqSetTest << std::endl;
}