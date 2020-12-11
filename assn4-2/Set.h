#ifndef SET_H_
#define SET_H_

#include "NODE.h"

template<typename T>
class Set //set�� ���� ����Ʈ���� ����ϱ� ������ ���� set���� ���� �ٸ�����, ���ǻ� �̸��� set���� ��(�ߺ����� ���+����Ʈ��)
{
private:
	int Size; //��� ���� ī����
	NODE<T>* head; //set�� head

public:
	int size() { return Size; }
	void insert(T data, int key);
	void sprint_all();
	NODE<T>* erase(NODE<T>* iter);
	NODE<T>* begin() { return head; }
	NODE<T>* end() { return nullptr; }
	Set<T>() : Size(0), head(nullptr) {}
	~Set<T>();
};


template<typename T>
void Set<T>::insert(T data, int key) //set�� ���������� �ǰ� ����, �ߺ��� ����
{
	NODE<T>* walk; //��� ��ġ Ž����
	for (walk = head; walk != nullptr; walk = walk->get_next())
	{
		if (walk->get_data() == data) //�̹� set�� ���� �����Ͱ� �����ϴ� ���
			return; //set�� ������ϰ� ����
	}

	NODE<T>* node = new NODE<T>; //������ ����� ���
	node->set_data(data); //��忡 ������ ����

	if (Size == 0 || node->get_data() < head->get_data()) //set�� ó���� �����ϴ� ���(�� set �Ǵ� ���� ���� data)
	{
		node->set_next(head); //head�� ���� ����Ǿ� �ִ� node�� ���θ��� node�� ������ ����
		head = node; //node�� head�� �����
	}

	else //����Ʈ�� �߰� �Ǵ� ���� �����ϴ� ���
	{
		for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
		{
			if (node->get_data() < walk->get_next()->get_data()) //walk�� ���� ��ġ�� �����Ͱ� node�� �����ͺ��� ũ��
				break; //walk�� walk->next ���̿� �����ؾ���(��������)
		}

		node->set_next(walk->get_next()); //node�� next�� walk�� next�� ����
		walk->set_next(node); //walk�� ������ node�� ����
	}

	Size++; //������++
}

template<> inline void Set<Pair<int, std::string>>::insert(Pair<int, std::string> data, int key) //Ư��ȭ(int, string �� ���ؼ�)
{
	NODE<Pair<int, std::string>>* walk; //��� ��ġ Ž����
	for (walk = head; walk != nullptr; walk = walk->get_next())
	{
		if (walk->get_data() == data) //�̹� set�� ���� �����Ͱ� �����ϴ� ���
			return; //set�� ������ϰ� ����
	}

	NODE<Pair<int, std::string>>* node = new NODE<Pair<int, std::string>>; //������ ����� ���
	node->set_data(data); //��忡 ������ ����

	if (key == 0) //first�� �켱 ���ı�������
	{
		if (Size == 0 || node->get_data() < head->get_data()) //set�� ó���� �����ϴ� ���(�� set �Ǵ� ���� ���� data)
		{
			node->set_next(head); //head�� ���� ����Ǿ� �ִ� node�� ���θ��� node�� ������ ����
			head = node; //node�� head�� �����
		}

		else //����Ʈ�� �߰� �Ǵ� ���� �����ϴ� ���
		{
			for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
			{
				if (node->get_data() < walk->get_next()->get_data()) //walk�� ���� ��ġ�� �����Ͱ� node�� �����ͺ��� ũ��
					break; //walk�� walk->next ���̿� �����ؾ���(��������)
			}

			node->set_next(walk->get_next()); //node�� next�� walk�� next�� ����
			walk->set_next(node); //walk�� ������ node�� ����
		}
	}

	else //second�� �켱 ���� ��������
	{
		if (Size == 0 || node->get_data().second < head->get_data().second || (node->get_data().second == head->get_data().second && node->get_data().first < head->get_data().first)) //set�� ó���� �����ϴ� ���(�� set �Ǵ� ���� ���� data)
		{
			node->set_next(head); //head�� ���� ����Ǿ� �ִ� node�� ���θ��� node�� ������ ����
			head = node; //node�� head�� �����
		}

		else //����Ʈ�� �߰� �Ǵ� ���� �����ϴ� ���
		{
			for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
			{
				if (node->get_data().second < walk->get_next()->get_data().second || 
					(node->get_data().second == walk->get_next()->get_data().second && node->get_data().first < walk->get_next()->get_data().first)) //walk�� ���� ��ġ�� �����Ͱ� node�� �����ͺ��� ũ��
					break; //walk�� walk->next ���̿� �����ؾ���(��������)
			}

			node->set_next(walk->get_next()); //node�� next�� walk�� next�� ����
			walk->set_next(node); //walk�� ������ node�� ����
		}
	}

	Size++; //������++
}

template<typename T>
void Set<T>::sprint_all() //ó������ ������ ���
{
	for (NODE<T>* walk = head; walk != nullptr; walk = walk->get_next())
		std::cout << walk->get_data() << std::endl;
}

template<typename T>
NODE<T>* Set<T>::erase(NODE<T>* iter)
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
Set<T>::~Set() //�Ҹ��� �����Ҵ� ����
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
