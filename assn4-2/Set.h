#ifndef SET_H_
#define SET_H_

#include "NODE.h"

template<typename T>
class Set //set은 원래 이진트리를 사용하기 때문에 실제 set과는 많이 다르지만, 편의상 이름을 set으로 함(중복무시 기능+리스트임)
{
private:
	int Size; //노드 개수 카운팅
	NODE<T>* head; //set의 head

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
void Set<T>::insert(T data, int key) //set이 오름차순이 되게 삽입, 중복은 무시
{
	NODE<T>* walk; //노드 위치 탐색용
	for (walk = head; walk != nullptr; walk = walk->get_next())
	{
		if (walk->get_data() == data) //이미 set에 같은 데이터가 존재하는 경우
			return; //set에 저장안하고 종료
	}

	NODE<T>* node = new NODE<T>; //데이터 저장용 노드
	node->set_data(data); //노드에 데이터 저장

	if (Size == 0 || node->get_data() < head->get_data()) //set의 처음에 삽입하는 경우(빈 set 또는 가장 작은 data)
	{
		node->set_next(head); //head에 원래 연결되어 있던 node를 새로만든 node의 다음에 연결
		head = node; //node가 head에 연결됨
	}

	else //리스트의 중간 또는 끝에 삽입하는 경우
	{
		for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
		{
			if (node->get_data() < walk->get_next()->get_data()) //walk의 다음 위치의 데이터가 node의 데이터보다 크면
				break; //walk와 walk->next 사이에 저장해야함(오름차순)
		}

		node->set_next(walk->get_next()); //node의 next를 walk의 next로 연결
		walk->set_next(node); //walk의 다음을 node로 변경
	}

	Size++; //사이즈++
}

template<> inline void Set<Pair<int, std::string>>::insert(Pair<int, std::string> data, int key) //특수화(int, string 페어에 대해서)
{
	NODE<Pair<int, std::string>>* walk; //노드 위치 탐색용
	for (walk = head; walk != nullptr; walk = walk->get_next())
	{
		if (walk->get_data() == data) //이미 set에 같은 데이터가 존재하는 경우
			return; //set에 저장안하고 종료
	}

	NODE<Pair<int, std::string>>* node = new NODE<Pair<int, std::string>>; //데이터 저장용 노드
	node->set_data(data); //노드에 데이터 저장

	if (key == 0) //first를 우선 정렬기준으로
	{
		if (Size == 0 || node->get_data() < head->get_data()) //set의 처음에 삽입하는 경우(빈 set 또는 가장 작은 data)
		{
			node->set_next(head); //head에 원래 연결되어 있던 node를 새로만든 node의 다음에 연결
			head = node; //node가 head에 연결됨
		}

		else //리스트의 중간 또는 끝에 삽입하는 경우
		{
			for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
			{
				if (node->get_data() < walk->get_next()->get_data()) //walk의 다음 위치의 데이터가 node의 데이터보다 크면
					break; //walk와 walk->next 사이에 저장해야함(오름차순)
			}

			node->set_next(walk->get_next()); //node의 next를 walk의 next로 연결
			walk->set_next(node); //walk의 다음을 node로 변경
		}
	}

	else //second를 우선 정렬 기준으로
	{
		if (Size == 0 || node->get_data().second < head->get_data().second || (node->get_data().second == head->get_data().second && node->get_data().first < head->get_data().first)) //set의 처음에 삽입하는 경우(빈 set 또는 가장 작은 data)
		{
			node->set_next(head); //head에 원래 연결되어 있던 node를 새로만든 node의 다음에 연결
			head = node; //node가 head에 연결됨
		}

		else //리스트의 중간 또는 끝에 삽입하는 경우
		{
			for (walk = head; walk->get_next() != nullptr; walk = walk->get_next())
			{
				if (node->get_data().second < walk->get_next()->get_data().second || 
					(node->get_data().second == walk->get_next()->get_data().second && node->get_data().first < walk->get_next()->get_data().first)) //walk의 다음 위치의 데이터가 node의 데이터보다 크면
					break; //walk와 walk->next 사이에 저장해야함(오름차순)
			}

			node->set_next(walk->get_next()); //node의 next를 walk의 next로 연결
			walk->set_next(node); //walk의 다음을 node로 변경
		}
	}

	Size++; //사이즈++
}

template<typename T>
void Set<T>::sprint_all() //처음부터 끝까지 출력
{
	for (NODE<T>* walk = head; walk != nullptr; walk = walk->get_next())
		std::cout << walk->get_data() << std::endl;
}

template<typename T>
NODE<T>* Set<T>::erase(NODE<T>* iter)
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
Set<T>::~Set() //소멸자 동적할당 해제
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
