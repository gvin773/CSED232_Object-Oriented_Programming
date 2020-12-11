#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include "Vector.h"
#include "Set.h"

int pokemon_num[26]; //�÷��̾ ���� ���ϸ� �� ����
std::string pokemon[26] = { "bulbasaur", "ivysaur", "venusaur", "charmander", "charmeleon",
						   "charizard", "squirtle", "wartortle", "blastoise", "caterpie",
						   "metapod", "butterfree", "weedle", "kakuna", "beedrill",
						   "pidgey", "pidgeotto", "pidgeot", "rattata", "raticate",
						   "spearow", "fearow", "ekans", "arbok", "pikachu", "raichu" };

inline void print_menu();
bool check_command(const std::string& com, char last);
bool check_index(const std::string& index);

bool gathering(Vector<Pair<int, std::string>>& list_time, Set<Pair<int, std::string>>& list_num, Set<Pair<int, std::string>>& list_name); //ä��
void encyclopedia(Vector<Pair<int, std::string>>& list_time, Set<Pair<int, std::string>>& list_num, Set<Pair<int, std::string>>& list_name); //����

bool find(std::string s, NODE<Pair<int, std::string>>* n);

int main()
{
	std::srand((unsigned int)time(NULL)); //�õ�

	Vector<Pair<int, std::string>> list_time; //���� ������� ����, �ߺ�o
	Set<Pair<int, std::string>> list_num; //�ε��� ������� ����, �ߺ�x
	Set<Pair<int, std::string>> list_name; //�̸� ������� ����, �ߺ�x

	while (1)
	{
		system("cls");
		print_menu();

		std::string command;
		std::getline(std::cin, command);
		while (!check_command(command, '3')) //������ 3��
		{
			std::cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �� �ϳ��� ���ڸ� �Է����ּ���." << std::endl;
			std::cout << ">> ";
			std::getline(std::cin, command);
		}

		if (command[0] == '1') //ä��
		{
			while (1)
			{
				if (!gathering(list_time, list_num, list_name))
					break;
			}
		}

		else if (command[0] == '2') //����
			encyclopedia(list_time, list_num, list_name);

		else //����
		{
			std::cout << "���α׷��� �����մϴ�..." << std::endl;
			Sleep(500);
			break;
		}
	}

	return 0;
}

inline void print_menu()
{
	std::cout << "1. ä��" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << ">> ";
}

bool check_command(const std::string& com, char last)
{
	if (com.size() != 1) return false;
	if ('1' <= com[0] && com[0] <= last) return true; //���� �Է�
	else return false;
}

bool check_index(const std::string& index)
{
	if (!(1 <= index.size() && index.size() <= 2)) return false;
	if (index.size() == 1) //1����
	{
		if (!('1' <= index[0] && index[0] <= '9')) return false; //���ڰ� �ƴ� ���
		if (pokemon_num[index[0] - '0' - 1] == 0) return false; //������ ���� ���� ���ϸ��� �ε����� ���
		return true; //���� �Է�
	}
	else //2����
	{
		if (!('1' <= index[0] && index[0] <= '2')) return false; //���� �ڸ����� 1, 2�� �ƴ� ���
		if (!('0' <= index[1] && index[1] <= '9')) return false; //���� �ڸ��� ���ڰ� �ƴ� ���
		int i = 10 * (index[0] - '0') + index[1] - '0'; //�ε��� ������ ����
		if (!(10 <= i && i <= 26)) return false; //10-26�� �ƴ� �߸��� ����
		if (pokemon_num[i - 1] == 0) return false; //������ ���� ���� ���ϸ��� �ε����� ���
		return true; //�����Է�
	}
}

bool gathering(Vector<Pair<int, std::string>>& list_time, Set<Pair<int, std::string>>& list_num, Set<Pair<int, std::string>>& list_name) //ä��
{
	int index = std::rand() % 26; //index
	std::string com; //command
	std::cout << pokemon[index] << "��(��) ��Ÿ����!" << std::endl;
	std::cout << "1. ��´�.\n" << "2. ��������.\n" << ">> ";

	std::getline(std::cin, com);
	while (!check_command(com, '2')) //������ 2��
	{
		std::cout << "�߸��� �Է��Դϴ�. 1, 2 �� �ϳ��� ���ڸ� �Է����ּ���." << std::endl;
		std::cout << ">> ";
		std::getline(std::cin, com);
	}

	if (com[0] == '1') //��´�
	{
		pokemon_num[index]++;
		list_time.push_back(make_Pair(index + 1, pokemon[index]));
		list_num.insert(make_Pair(index + 1, pokemon[index]), 0);
		list_name.insert(make_Pair(index + 1, pokemon[index]), 1);
		std::cout << pokemon[index] << "��(��) ��ҽ��ϴ�!" << std::endl << std::endl;
		Sleep(1000);
		return true;
	}

	else //����ģ��
	{
		std::cout << "������ �����ƴ�!";
		Sleep(1000);
		return false;
	}
}

void encyclopedia(Vector<Pair<int, std::string>>& list_time, Set<Pair<int, std::string>>& list_num, Set<Pair<int, std::string>>& list_name) //����
{
	while (1)
	{
		system("cls");
		list_time.vprint_all();

		std::cout << "\n1. ��ȣ�� ����\n";
		std::cout << "2. �̸��� ����\n";
		std::cout << "3. �˻�\n";
		std::cout << "4. �����ֱ�\n";
		std::cout << "5. ������\n";
		std::cout << ">> ";

		std::string com;
		std::getline(std::cin, com);
		while (!check_command(com, '5')) //������ 5��
		{
			std::cout << "�߸��� �Է��Դϴ�. 1, 2, 3, 4, 5 �� �ϳ��� ���ڸ� �Է����ּ���." << std::endl;
			std::cout << ">> ";
			std::getline(std::cin, com);
		}

		if (com[0] == '1') //��ȣ�� ����
		{
			std::cout << "\n��ȣ�� ���� ���\n";
			list_num.sprint_all();
		}

		else if (com[0] == '2') //�̸��� ����
		{
			std::cout << "\n�̸��� ���� ���\n";
			list_name.sprint_all();
		}

		else if (com[0] == '3') //�˻�
		{
			std::cout << "\n���ϸ� �̸��� �Է�����" << std::endl;
			std::cout << ">> ";
			std::string name;
			getline(std::cin, name);

			bool nofound = true;
			std::cout << std::endl << name << "��(��) ���� ���ϸ��� ã�� ���̾�" << std::endl;
			for (auto iter = list_name.begin(); iter != list_name.end(); iter = iter->npp())
			{
				if (find(name, iter)) //ã������
				{
					std::cout << iter->get_data() << " " << pokemon_num[iter->get_data().first - 1] << "����" << std::endl;
					nofound = false;
				}
			}

			if (nofound) std::cout << "\n�׷� ���ϸ��� ����" << std::endl;
			else std::cout << std::endl << name << "��(��) ���� ���ϸ��� ��� ã�Ҿ�" << std::endl;
		}

		else if (com[0] == '4') //�����ֱ�
		{
			bool nopokemon = true;
			for (int i = 0; i < 26; i++)
			{
				if (pokemon_num[i] != 0)
				{
					nopokemon = false;
					break;
				}
			}

			if (nopokemon)
			{
				std::cout << "������ �ִ� ���ϸ��� �������� �ʽ��ϴ�. �������� ���ư��ϴ�...";
				Sleep(500);
				continue;
			}

			std::cout << "������ �����ٷ�? ��ȣ�� �Է�����" << std::endl;
			std::cout << ">> ";

			std::string index;
			std::getline(std::cin, index);
			while (!check_index(index))
			{
				std::cout << "�߸��� �Է��Դϴ�. 1-26 ������ ���ڸ� �Է��ϼ̴���, ������ �ִ� ���ϸ��� ���ڸ� �Է��ϼ̴��� Ȯ�����ּ���." << std::endl;
				std::cout << ">> ";
				std::getline(std::cin, index);
			}

			int i;
			if (index.size() == 1) i = index[0] - '0';
			else i = 10 * (index[0] - '0') + index[1] - '0';
			//index ����ȭ

			int cnt = 0, re = list_time.size();
			for (auto iter = list_time.begin(); cnt < re; cnt++)
			{
				if (iter->get_data() == make_Pair(i, pokemon[i - 1]))
				{
					pokemon_num[i - 1]--;
					iter = list_time.erase(iter);
				}
				else iter = iter->npp();
			} //���� �ε��� ��� ���ϸ� ����

			cnt = 0, re = list_num.size();
			for (auto iter = list_num.begin(); cnt < re; cnt++)
			{
				if (iter->get_data() == make_Pair(i, pokemon[i - 1])) iter = list_num.erase(iter);
				else iter = iter->npp();
			} //���� �ε��� ��� ���ϸ� ����

			cnt = 0, re = list_name.size();
			for (auto iter = list_name.begin(); cnt < re; cnt++)
			{
				if (iter->get_data() == make_Pair(i, pokemon[i - 1])) iter = list_name.erase(iter);
				else iter = iter->npp();
			} //���� �ε��� ��� ���ϸ� ����

			std::cout << "�� �� " << pokemon[i - 1] << '~' << std::endl;
		}

		else //������
		{
			std::cout << "�������� ���ư��ϴ�...";
			Sleep(1000);
			return;
		}

		std::cout << "\n1. �������� ���ư���" << std::endl;
		std::cout << "2. �������� ���ư���" << std::endl;
		std::cout << ">> ";

		std::string backto;
		getline(std::cin, backto);
		while (!check_command(backto, '2')) //������ 2��
		{
			std::cout << "�߸��� �Է��Դϴ�. 1, 2 �� �ϳ��� ���ڸ� �Է����ּ���." << std::endl;
			std::cout << ">> ";
			std::getline(std::cin, backto);
		}

		if (backto[0] == '1') //�������� ���ư���
		{
			std::cout << "�������� ���ư��ϴ�...";
			Sleep(1000);
		}

		if (backto[0] == '2') //�������� ���ư���
		{
			std::cout << "�������� ���ư��ϴ�...";
			Sleep(1000);
			return;
		}
	}
}

bool find(std::string s, NODE<Pair<int, std::string>>* n)
{
	if (n->get_data().second.find(s) != std::string::npos) return true; //s�� ã������
	else return false; //��ã������
}
