#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>

int pokemon_num[26]; //플레이어가 잡은 포켓몬 수 저장
std::string pokemon[26] = { "bulbasaur", "ivysaur", "venusaur", "charmander", "charmeleon",
						   "charizard", "squirtle", "wartortle", "blastoise", "caterpie",
						   "metapod", "butterfree", "weedle", "kakuna", "beedrill",
						   "pidgey", "pidgeotto", "pidgeot", "rattata", "raticate",
						   "spearow", "fearow", "ekans", "arbok", "pikachu", "raichu" };

typedef std::pair<int, std::string> pis;

inline void print_menu();
bool check_command(const std::string& com, char last);
bool check_index(const std::string& index);

struct compare_name //list_name에서 사용할 key (이름기준 오름차순)
{
	bool operator() (const pis& a, const pis& b) const
	{
		return a.second < b.second;
	}
};

bool gathering(std::vector<pis>& list_time, std::set<pis>& list_num, std::set<pis, compare_name>& list_name); //채집
void encyclopedia(std::vector<pis>& list_time, std::set<pis>& list_num, std::set<pis, compare_name>& list_name); //도감

int main()
{
	std::srand((unsigned int)time(NULL)); //시드

	std::vector<pis> list_time; //잡은 순서대로 정렬, 중복o
	std::set<pis> list_num; //인덱스 순서대로 정렬, 중복x
	std::set<pis, compare_name> list_name; //이름 순서대로 정렬, 중복x

	while (1)
	{
		system("cls");
		print_menu();

		std::string command;
		std::getline(std::cin, command);
		while (!check_command(command, '3')) //선택지 3개
		{
			std::cout << "잘못된 입력입니다. 1, 2, 3 중 하나의 숫자를 입력해주세요." << std::endl;
			std::cout << ">> ";
			std::getline(std::cin, command);
		}

		if (command[0] == '1') //채집
		{
			while (1)
			{
				if (!gathering(list_time, list_num, list_name))
					break;
			}
		}

		else if (command[0] == '2') //도감
			encyclopedia(list_time, list_num, list_name);

		else //종료
		{
			std::cout << "프로그램을 종료합니다..." << std::endl;
			Sleep(500);
			break;
		}
	}

	return 0;
}

inline void print_menu()
{
	std::cout << "1. 채집" << std::endl;
	std::cout << "2. 도감" << std::endl;
	std::cout << "3. 종료" << std::endl;
	std::cout << ">> ";
}

bool check_command(const std::string& com, char last)
{
	if (com.size() != 1) return false;
	if ('1' <= com[0] && com[0] <= last) return true; //정상 입력
	else return false;
}

bool check_index(const std::string& index)
{
	if (!(1 <= index.size() && index.size() <= 2)) return false;
	if (index.size() == 1) //1글자
	{
		if (!('1' <= index[0] && index[0] <= '9')) return false; //숫자가 아닌 경우
		if (pokemon_num[index[0] - '0' - 1] == 0) return false; //가지고 있지 않은 포켓몬의 인덱스인 경우
		return true; //정상 입력
	}
	else //2글자
	{
		if (!('1' <= index[0] && index[0] <= '2')) return false; //십의 자리수가 1, 2가 아닌 경우
		if (!('0' <= index[1] && index[1] <= '9')) return false; //일의 자리가 숫자가 아닌 경우
		int i = 10 * (index[0] - '0') + index[1] - '0'; //인덱스 정수로 변경
		if (!(10 <= i && i <= 26)) return false; //10-26이 아닌 잘못된 정수
		if (pokemon_num[i - 1] == 0) return false; //가지고 있지 않은 포켓몬의 인덱스인 경우
		return true; //정상입력
	}
}

bool gathering(std::vector<pis>& list_time, std::set<pis>& list_num, std::set<pis, compare_name>& list_name) //채집
{
	int index = std::rand() % 26; //index
	std::string com; //command
	std::cout << pokemon[index] << "이(가) 나타났다!" << std::endl;
	std::cout << "1. 잡는다.\n" << "2. 도망간다.\n" << ">> ";

	std::getline(std::cin, com);
	while (!check_command(com, '2')) //선택지 2개
	{
		std::cout << "잘못된 입력입니다. 1, 2 중 하나의 숫자를 입력해주세요." << std::endl;
		std::cout << ">> ";
		std::getline(std::cin, com);
	}

	if (com[0] == '1') //잡는다
	{
		pokemon_num[index]++;
		list_time.push_back(make_pair(index + 1, pokemon[index]));
		list_num.insert(make_pair(index + 1, pokemon[index]));
		list_name.insert(make_pair(index + 1, pokemon[index]));
		std::cout << pokemon[index] << "을(를) 잡았습니다!" << std::endl << std::endl;
		Sleep(1000);
		return true;
	}

	else //도망친다
	{
		std::cout << "무사히 도망쳤다!";
		Sleep(1000);
		return false;
	}
}

void encyclopedia(std::vector<pis>& list_time, std::set<pis>& list_num, std::set<pis, compare_name>& list_name) //도감
{
	while (1)
	{
		system("cls");
		for (auto iter = list_time.begin(); iter != list_time.end(); iter++)
			std::cout << iter->first << ". " << iter->second << std::endl;

		std::cout << "\n1. 번호순 정렬\n";
		std::cout << "2. 이름순 정렬\n";
		std::cout << "3. 검색\n";
		std::cout << "4. 놓아주기\n";
		std::cout << "5. 나가기\n";
		std::cout << ">> ";

		std::string com;
		std::getline(std::cin, com);
		while (!check_command(com, '5')) //선택지 5개
		{
			std::cout << "잘못된 입력입니다. 1, 2, 3, 4, 5 중 하나의 숫자를 입력해주세요." << std::endl;
			std::cout << ">> ";
			std::getline(std::cin, com);
		}

		if (com[0] == '1') //번호순 정렬
		{
			std::cout << "\n번호순 정렬 결과\n";
			for (auto iter = list_num.begin(); iter != list_num.end(); iter++)
				std::cout << iter->first << ". " << iter->second << std::endl;
		}

		else if (com[0] == '2') //이름순 정렬
		{
			std::cout << "\n이름순 정렬 결과\n";
			for (auto iter = list_name.begin(); iter != list_name.end(); iter++)
				std::cout << iter->first << ". " << iter->second << std::endl;
		}

		else if (com[0] == '3') //검색
		{
			std::cout << "\n포켓몬 이름을 입력해줘" << std::endl;
			std::cout << ">> ";
			std::string name;
			getline(std::cin, name);

			bool nofound = true;
			std::cout << std::endl << name << "이(가) 들어가는 포켓몬을 찾는 중이야" << std::endl;
			for (auto iter = list_name.begin(); iter != list_name.end(); iter++)
			{
				if (iter->second.find(name) != std::string::npos) //찾았으면
				{
					std::cout << iter->first << ". " << iter->second << " " << pokemon_num[iter->first - 1] << "마리" << std::endl;
					nofound = false;
				}
			}

			if (nofound) std::cout << "\n그런 포켓몬은 없어" << std::endl;
			else std::cout << std::endl << name << "이(가) 들어가는 포켓몬을 모두 찾았어" << std::endl;
		}

		else if (com[0] == '4') //놓아주기
		{
			std::cout << "누구를 놓아줄래? 번호를 입력해줘" << std::endl;
			std::cout << ">> ";

			std::string index;
			std::getline(std::cin, index);
			while (!check_index(index))
			{
				std::cout << "잘못된 입력입니다. 1-26 사이의 숫자를 입력하셨는지, 가지고 있는 포켓몬의 숫자를 입력하셨는지 확인해주세요." << std::endl;
				std::cout << ">> ";
				std::getline(std::cin, index);
			}

			int i;
			if (index.size() == 1) i = index[0] - '0';
			else i = 10 * (index[0] - '0') + index[1] - '0';
			//index 정수화

			for (auto iter = list_time.begin(); iter != list_time.end();)
			{
				if (iter->first == i)
				{
					pokemon_num[iter->first - 1]--;
					iter = list_time.erase(iter);
				}
				else iter++;
			} //같은 인덱스 모든 포켓몬 제거

			for (auto iter = list_num.begin(); iter != list_num.end();)
			{
				if (iter->first == i) list_num.erase(iter++);
				else iter++;
			} //같은 인덱스 모든 포켓몬 제거

			for (auto iter = list_name.begin(); iter != list_name.end();)
			{
				if (iter->first == i) list_name.erase(iter++);
				else iter++;
			} //같은 인덱스 모든 포켓몬 제거

			std::cout << "잘 가 " << pokemon[i - 1] << '~' << std::endl;
		}

		else //나가기
		{
			std::cout << "메인으로 돌아갑니다...";
			Sleep(1000);
			return;
		}

		std::cout << "\n1. 도감으로 돌아가기" << std::endl;
		std::cout << "2. 메인으로 돌아가기" << std::endl;
		std::cout << ">> ";

		std::string backto;
		getline(std::cin, backto);
		while (!check_command(backto, '2')) //선택지 2개
		{
			std::cout << "잘못된 입력입니다. 1, 2 중 하나의 숫자를 입력해주세요." << std::endl;
			std::cout << ">> ";
			std::getline(std::cin, backto);
		}

		if (backto[0] == '1') //도감으로 돌아가기
		{
			std::cout << "도감으로 돌아갑니다...";
			Sleep(1000);
		}

		if (backto[0] == '2') //메인으로 돌아가기
		{
			std::cout << "메인으로 돌아갑니다...";
			Sleep(1000);
			return;
		}
	}
}
