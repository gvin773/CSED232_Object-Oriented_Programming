#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include "Pair.h"

template<typename T>
class NODE
{
private:
	T data; //포켓몬 데이터
	NODE<T>* next; //노드연결용

public:
	NODE<T>() : next(nullptr) {}
	NODE<T>(T d, NODE<T>* n) : data(d), next(n) {}
	void set_data(T data);
	void set_next(NODE<T>* next);
	T get_data() { return data; }
	NODE<T>* get_next() { return next; }
	NODE<T>* npp() { return get_next(); }
};

template<typename T>
void NODE<T>::set_data(T data)
{
	this->data = data;
}

template<typename T>
void NODE<T>::set_next(NODE<T>* next)
{
	this->next = next;
}

#endif
