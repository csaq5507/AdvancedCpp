#pragma once

template <int N>
constexpr int Factorial() {
	return N * Factorial<N - 1>();
}
template <>
constexpr int Factorial<0>() {
	return 1;
}

template <>
constexpr int Factorial<1>() {
	return 1;
}

template <long long N, long long M>
struct Ackerman {
	const static long long value = Ackerman<N - 1, Ackerman<N, M - 1>::value>::value;
};


template <long long M>
struct Ackerman<0, M> {
	const static long long value = M + 1;
};


template <long long N>
struct Ackerman<N, 0> {
	const static long long value = Ackerman<N - 1, 1>::value;
};

//Source: David Vandevoorde, Nicolai M. Josuttis, Douglas Gregor-C++ Templates_ The Complete Guide-Addison-Wesley (2017)
//problem each path of the ? operator gets instanciated
//e.g. value = (3 < 2 * 2) ? Sqrt<3, 1, 1>::value : Sqrt<2, 2, 10>::value then Sqrt<3, 1, 1>::value and  Sqrt<2, 2, 10>::value gets instanciated recursively 
//and a template instanciation even a moderate one needs at least some kilobytes
template<int N, int	LO = 1,	int	HI = N>
struct Sqrt {
	static constexpr auto mid = (LO + HI + 1) / 2;

	static constexpr auto value = (N < mid * mid) ? Sqrt<N, LO, mid - 1>::value : Sqrt<N, mid, HI>::value;
};

template<int N, int	M>
struct Sqrt<N,M,M> {
	static constexpr auto value = N;
};

//now we fix this problem of sqrt
template<bool Cond, typename TrueType, typename FalseType>
struct IfThenElseT {
	using Type = TrueType;
};

template<typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType> {
	using Type = FalseType;
};
template<bool Cond, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<Cond, TrueType, FalseType>::Type;


template<int N, int	LO = 1, int	HI = N>
struct OptSqrt {
	static constexpr auto mid = (LO + HI + 1) / 2;

	using SubT = IfThenElse<(N < mid * mid),
							OptSqrt<N, LO, mid - 1>,
							OptSqrt<N, mid, HI>
						   >;

	static constexpr auto value = SubT::value;
};

template<int N, int	M>
struct OptSqrt<N, M, M> {
	static constexpr auto value = N;
};