#ifndef VECTOR_H_
#define VECTOR_H_

#include "NODE.h"

template<typename T>
class Vector //vector가 아닌 리스트지만 편의상 이름을 vector로 함
{
private:
	int Size; //노드 개수 카운팅
	NODE<T>* head; //vector의 head

public:
	int size() { return Size; }
	void push_back(T data);
	void vprint_all();
	NODE<T>* erase(NODE<T>* iter);
	NODE<T>* begin() { return head; }
	NODE<T>* end() { return nullptr; }
	Vector<T>() : Size(0), head(nullptr) {}
	~Vector<T>();
};

template<typename T>
void Vector<T>::push_back(T data) //끝에 삽입
{
	NODE<T>* node = new NODE<T>; //데이터 저장용 노드
	NODE<T>* walk; //노드 위치 탐색용

	node->set_data(data); //노드에 데이터 저장
	
	if (head == nullptr) //첫 삽입
	{
		head = node;
		head->set_next(nullptr);
		Size++;
		return;
	}

	for (walk = head; walk->get_next() != nullptr; walk = walk->get_next()) //벡터(리스트) 제일 끝 찾음
		;

	node->set_next(nullptr); //노드의 끝을 nullptr로 세팅
	walk->set_next(node); //벡터의 끝에 node 연결
	
	Size++; //사이즈++
}

template<typename T>
void Vector<T>::vprint_all() //처음부터 끝까지 출력
{
	for (NODE<T>* walk = head; walk != nullptr; walk = walk->get_next())
		std::cout << walk->get_data() << std::endl;
}

template<typename T>
NODE<T>* Vector<T>::erase(NODE<T>* iter)
{
	if (iter == nullptr) return nullptr; //nullptr 예외처리
	if (head == iter) //첫 원소를 지우는 경우
	{
		head = iter->get_next();
		delete iter;
		Size--;
		return head;
	}
	NODE<T>* walk;
	for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
	{
		if (walk->get_next() == iter) break;
	}

	NODE<T>* temp = walk->get_next(); //지워야할 노드 저장
	walk->set_next(walk->get_next()->get_next()); //지워야할 노드 앞뒤 연결
	delete temp; //노드 삭제
	Size--;
	return walk->get_next(); //다음 노드 리턴
}

template<typename T>
Vector<T>::~Vector() //소멸자 동적할당 해제
{
	if (head != nullptr) //head==nullptr이면 아무것도 없음
	{
		NODE<T>* walk; //노드 위치 탐색용
		for (walk = head; walk->get_next() != nullptr;)
		{
			NODE<T>* next = walk->get_next();
			delete walk;
			walk = next;
		}
	}
}

#endif