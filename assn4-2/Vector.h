#ifndef VECTOR_H_
#define VECTOR_H_

#include "NODE.h"

template<typename T>
class Vector //vector�� �ƴ� ����Ʈ���� ���ǻ� �̸��� vector�� ��
{
private:
	int Size; //��� ���� ī����
	NODE<T>* head; //vector�� head

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
void Vector<T>::push_back(T data) //���� ����
{
	NODE<T>* node = new NODE<T>; //������ ����� ���
	NODE<T>* walk; //��� ��ġ Ž����

	node->set_data(data); //��忡 ������ ����
	
	if (head == nullptr) //ù ����
	{
		head = node;
		head->set_next(nullptr);
		Size++;
		return;
	}

	for (walk = head; walk->get_next() != nullptr; walk = walk->get_next()) //����(����Ʈ) ���� �� ã��
		;

	node->set_next(nullptr); //����� ���� nullptr�� ����
	walk->set_next(node); //������ ���� node ����
	
	Size++; //������++
}

template<typename T>
void Vector<T>::vprint_all() //ó������ ������ ���
{
	for (NODE<T>* walk = head; walk != nullptr; walk = walk->get_next())
		std::cout << walk->get_data() << std::endl;
}

template<typename T>
NODE<T>* Vector<T>::erase(NODE<T>* iter)
{
	if (iter == nullptr) return nullptr; //nullptr ����ó��
	if (head == iter) //ù ���Ҹ� ����� ���
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

	NODE<T>* temp = walk->get_next(); //�������� ��� ����
	walk->set_next(walk->get_next()->get_next()); //�������� ��� �յ� ����
	delete temp; //��� ����
	Size--;
	return walk->get_next(); //���� ��� ����
}

template<typename T>
Vector<T>::~Vector() //�Ҹ��� �����Ҵ� ����
{
	if (head != nullptr) //head==nullptr�̸� �ƹ��͵� ����
	{
		NODE<T>* walk; //��� ��ġ Ž����
		for (walk = head; walk->get_next() != nullptr;)
		{
			NODE<T>* next = walk->get_next();
			delete walk;
			walk = next;
		}
	}
}

#endif