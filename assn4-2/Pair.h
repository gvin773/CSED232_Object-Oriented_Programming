#ifndef PAIR_H_
#define PAIR_H_

#include <iostream>
#include <string>
template <typename T1, typename T2>
class Pair //first, second 자유롭게 접근 가능
{
public:
	T1 first;
	T2 second;
	
	Pair<T1, T2>() {}
	Pair<T1, T2>(T1 a, T2 b) : first(a), second(b) {}

	template<typename T3, typename T4>
	friend std::ostream& operator<<(std::ostream& os, const Pair<T3, T4>& p);
	bool operator==(Pair<T1, T2> p) { return first == p.first && second == p.second; }
	bool operator<(Pair<T1, T2> p) const { if (first == p.first) return second < p.second; return first < p.first; }
};

template<typename T1, typename T2>
Pair<T1, T2> make_Pair(T1 a, T2 b)
{
	Pair<T1, T2> p(a, b);
	return p;
}

template<typename T3, typename T4>
std::ostream& operator<<(std::ostream& os, const Pair<T3, T4>& p)
{
	std::cout << p.first << ". " << p.second;
	return os;
}

#endif
