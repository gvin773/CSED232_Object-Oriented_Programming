#include <windows.h>
#include <ctime>
#include "CTrainer.h"
#include "CRival.h"

void ready(CTrainer& trainer, CRival& rival); //��Ʋ�غ�
void fight(CTrainer& trainer, CRival& rival); //��Ʋ����
int turn_trainer(CTrainer& trainer, CRival& rival); //Ʈ���̳� ��
int turn_rival(CTrainer& trainer, CRival& rival); //���̹� ��
void show_board(CTrainer& trainer, CRival& rival); //��Ʋ ���� �� ���ϸ� �̸�, ü�� ǥ��
double compatibility(std::string attack, std::string attacked); //�� üũ

void choose(CTrainer& trainer); //Ʈ���̳� ���ϸ� ����
void choose_rival(CRival& rival); //���̹� ���ϸ� ����

inline void gameexit(); //��������

int main()
{
	srand((unsigned int)time(NULL)); //�õ巣��

	CTrainer trainer;
	CRival rival;

	while (1)
	{
		system("cls");
		std::cout << "1. ��Ʋ�ϱ�" << std::endl;
		std::cout << "2. ���ϸ� ����" << std::endl;
		std::cout << "3. ����" << std::endl;

		int n;
		std::cin >> n; //�޴��Է�
		system("cls");
		if (n == 1) //��Ʋ
		{
			if (!trainer.check()) //���ϸ� ������ ���� �ʾ�����
			{
				std::cout << "��� ���ϸ��� ���õ��� �ʾҽ��ϴ�. ���� ���ϸ��� ������ �ּ���." << std::endl;
				std::cout << "�޴��� ���ư��ϴ�..." << std::endl;
				Sleep(1000);
				continue;
			}
			ready(trainer, rival); //��Ʋ�غ�
			fight(trainer, rival); //��Ʋ����
			trainer.init(); //Ʈ���̳� ���� �ʱ�ȭ
			rival.init(); //���̹� ���� �ʱ�ȭ
		}
		else if (n == 2) choose(trainer); //���ϸ���
		else if (n == 3) break; //����
		else std::cout << "1, 2, 3 �� �ϳ��� ���ڸ� �Է����ּ���!" << std::endl; //����ó��
		Sleep(1000);
	}

	gameexit(); //��������޽���
	return 0;
}

void ready(CTrainer& trainer, CRival& rival) //��Ʋ�غ�
{
	choose_rival(rival); //���̹� ���ϸ� ����

	std::cout << "�Ժ�Ÿ��� ���� ���� ȯ���մϴ�." << std::endl;
	trainer.show_info();
	std::cout << std::endl;
	rival.show_info();
	std::cout << std::endl << "��� �� ��Ʋ�� ���۵˴ϴ�.";
	Sleep(3000);
	system("cls");
}

void fight(CTrainer& trainer, CRival& rival) //��Ʋ����
{
	while (1)
	{
		if (trainer.get_speed() >= rival.get_speed()) //Ʈ���̳� ���� ����
		{
			while (1)
			{
				int tt = turn_trainer(trainer, rival);
				if (tt == 1) break; //������ϸ��� �������� ���İ� �ٽ� ���ؾ���
				else if (tt == 100) return; //������ ����Ǿ����Ƿ� �޴��� ���ư�
				Sleep(1500);
				int tr = turn_rival(trainer, rival);
				if (tr == 1) break; //�� ���ϸ��� �������� ���İ� �ٽ� ���ؾ���
				else if (tr == 100) return; //������ ����Ǿ����Ƿ� �޴��� ���ư�
				Sleep(1500);
			}
		}

		else //���̹� ���� ����
		{
			while (1)
			{
				int tr = turn_rival(trainer, rival);
				if (tr == 1) break; //�� ���ϸ��� �������� ���İ� �ٽ� ���ؾ���
				else if (tr == 100) return; //������ ����Ǿ����Ƿ� �޴��� ���ư�
				Sleep(1500);
				int tt = turn_trainer(trainer, rival);
				if (tt == 1) break; //������ϸ��� �������� ���İ� �ٽ� ���ؾ���
				else if (tt == 100) return; //������ ����Ǿ����Ƿ� �޴��� ���ư�
				Sleep(1500);
			}
		}
	}
}

int turn_trainer(CTrainer& trainer, CRival& rival) //Ʈ���̳� ��
{
	system("cls");
	show_board(trainer, rival);
	std::cout << "�� ���� �Ǿ���! ������ �ұ�?" << std::endl;
	while (1)
	{
		std::cout << "1. �ο��. " << "2. ���ϸ� " << "3. �׺�" << std::endl;
		int choice;
		std::cin >> choice;

		if (choice == 1) //��� ����
		{
			double mul = 0; //����
			int skill = trainer.battle(); //��� ����
			if (trainer.get_attack_type(skill) == trainer.get_main_type() || trainer.get_attack_type(skill) == trainer.get_sub_type()) mul = 1.5; //�ڼӺ���
			else mul = 1; //�⺻����
			mul *= compatibility(trainer.get_attack_type(skill), rival.get_main_type());
			mul *= compatibility(trainer.get_attack_type(skill), rival.get_sub_type()); //���� ���� ���� �Ϸ�

			double damage = 0; //�����
			if (mul != 0) //������ 0�̸� ����� 0
			{
				damage = (double)rival.get_defense() - ((double)trainer.get_attack() + mul * (double)trainer.get_skill_damage(skill)); //����� ���
				if (damage > 0) damage = -1; //����� ���
			}

			rival.set_hp(damage); //ü�� ����
			Sleep(2000);
			system("cls");
			show_board(trainer, rival); //����� ü�� �ݿ�
			if (damage == 0) std::cout << "ȿ���� ���� �� ����..." << std::endl;
			else if (mul <= 0.5) std::cout << "ȿ���� ������ �� �ϴ�..." << std::endl;
			else if (mul >= 2) std::cout << "ȿ���� �����ߴ�!" << std::endl;
			else std::cout << "ȿ���� ����ߴ�." << std::endl;

			if (rival.get_hp() == 0) //��� ���ϸ��� ������ ���
			{
				std::cout << "��� ���ϸ��� ��������!" << std::endl;
				Sleep(1500);
				rival.set_knock_down(); //knock_down �ݿ�
				rival.next(); //���� ���ϸ��� �����Ҵ� �����̸� ���� ���ϸ����� ����
				if (rival.get_in_battle() >= 3) //Ʈ���̳� �¸� ���� ����
				{
					std::cout << "��� ���ϸ��� ��� ��������!" << std::endl;
					std::cout << "*****�¸�*****" << std::endl;
					std::cout << "3�� �� �޴��� ���ư��ϴ�..." << std::endl;
					Sleep(3000);
					return 100; //��������
				}

				return 1;
			}

			break;
		}

		else if (choice == 2) //���ϸ� ��ü
		{
			if (trainer.change()) break; //�ڷΰ��Ⱑ �ƴϸ� ������
			system("cls");
			show_board(trainer, rival);
		}

		else if (choice == 3) //�׺� -> ��������
		{
			int ret = trainer.give_up();
			Sleep(1000);
			return ret; //��������
		}

		else //�߸��� �Է�
		{
			system("cls");
			std::cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �� �ϳ��� ���ڸ� �Է����ּ���." << std::endl;
			show_board(trainer, rival);
			continue;
		}
	}

	return 0;
}

int turn_rival(CTrainer& trainer, CRival& rival) //���̹� ��
{
	system("cls");
	show_board(trainer, rival);
	std::cout << "��� ���� �Ǿ���!" << std::endl;
	Sleep(1500);

	double mul = 0; //����
	int skill = rival.battle(); //����� ��� ����
	if (rival.get_attack_type(skill) == rival.get_main_type() || rival.get_attack_type(skill) == rival.get_sub_type()) mul = 1.5; //�ڼӺ���
	else mul = 1; //�⺻����
	mul *= compatibility(rival.get_attack_type(skill), trainer.get_main_type());
	mul *= compatibility(rival.get_attack_type(skill), trainer.get_sub_type()); //���� ���� ���� �Ϸ�

	double damage = 0; //�����
	if (mul != 0) //������ 0�̸� ����� 0
	{
		damage = (double)trainer.get_defense() - ((double)rival.get_attack() + mul * (double)rival.get_skill_damage(skill)); //����� ���
		if (damage > 0) damage = -1; //����� ���
	}

	trainer.set_hp(damage); //ü�� ����
	Sleep(2000);
	system("cls");
	show_board(trainer, rival); //����� ü�� �ݿ�
	if (damage == 0) std::cout << "ȿ���� ���� �� ����..." << std::endl;
	else if (mul <= 0.5) std::cout << "ȿ���� ������ �� �ϴ�..." << std::endl;
	else if (mul >= 2) std::cout << "ȿ���� �����ߴ�!" << std::endl;
	else std::cout << "ȿ���� ����ߴ�." << std::endl;

	if (trainer.get_hp() == 0) //���� ���ϸ��� �����Ҵ� �����̸�
	{
		trainer.set_knock_down(); //knock_down �ݿ�
		if (!trainer.isover()) //��ü������ ���ϸ��� �ִ� ���
		{
			std::cout << "�� ���ϸ��� ��������!" << std::endl;
			Sleep(1500);
			trainer.change_v2(); //��� ���ϸ��� �����Ҵ� ���°� �ƴϸ� �ٸ� ���ϸ����� ����
			return 1;
		}
		else //��ü������ ���ϸ� ���� ; ���̹� �¸� ���� ����
		{
			std::cout << "�� ���ϸ��� ��� ��������!" << std::endl;
			std::cout << "*****�й�*****" << std::endl;
			std::cout << "3�� �� �޴��� ���ư��ϴ�..." << std::endl;
			Sleep(3000);
			return 100; //��������
		}
	}

	return 0;
}

void show_board(CTrainer& trainer, CRival& rival) //��Ʋ ���� �� ���ϸ� �̸�, ü�� ǥ��
{
	trainer.show_battle_info();
	rival.show_battle_info();
}

double compatibility(std::string attack, std::string attacked) //�� üũ
{
	double ret = 1; //�󼺿� ���� ����
	if (attack == "����")
	{
		if (attacked == "����" || attacked == "Ǯ" || attacked == "�巡��") ret = 0.5;
		else if (attacked == "��" || attacked == "����") ret = 2;
		else if (attacked == "��") ret = 0;
	}
	else if (attack == "Ǯ")
	{
		if (attacked == "Ǯ" || attacked == "��" || attacked == "����" || attacked == "����" || attacked == "�巡��" || attacked == "��") ret = 0.5;
		else if (attacked == "��" || attacked == "����" || attacked == "�ٶ�") ret = 2;
	}
	else if (attack == "��")
	{
		if (attacked == "Ǯ" || attacked == "��" || attacked == "�巡��") ret = 0.5;
		else if (attacked == "��" || attacked == "����" || attacked == "��") ret = 2;
	}
	else if (attack == "��")
	{
		if (attacked == "��" || attacked == "��" || attacked == "�巡��" || attacked == "����") ret = 0.5;
		else if (attacked == "Ǯ" || attacked == "����") ret = 2;
	}
	else if (attack == "����")
	{
		if (attacked == "����" || attacked == "����") ret = 0.5;
		else if (attacked == "Ǯ" || attacked == "����") ret = 2;
	}
	else if (attack == "����")
	{
		if (attacked == "��" || attacked == "����" || attacked == "��" || attacked == "��Ʈ") ret = 0.5;
		else if (attacked == "Ǯ" || attacked == "������") ret = 2;
	}
	else if (attack == "�巡��")
	{
		if (attacked == "�巡��") ret = 2;
	}
	else if (attack == "������")
	{
		if (attacked == "������") ret = 0.5;
		else if (attacked == "��") ret = 2;
	}
	else if (attack == "��")
	{
		if (attacked == "��" || attacked == "��Ʈ" || attacked == "����" || attacked == "��") ret = 0.5;
		else if (attacked == "Ǯ") ret = 2;
	}
	else if (attack == "��Ʈ")
	{
		if (attacked == "������" || attacked == "��Ʈ") ret = 2;
		else if (attacked == "�븻") ret = 0;
	}

	else if (attack == "�븻")
	{
		if (attacked == "����") ret = 0.5;
		else if (attacked == "��Ʈ") ret = 0;
	}

	else if (attack == "����")
	{
		if (attacked == "��") ret = 0.5;
		else if (attacked == "��" || attacked == "����" || attacked == "����") ret = 2;
	}

	else if (attack == "��")
	{
		if (attacked == "Ǯ" || attacked == "����") ret = 0.5;
		else if (attacked == "����" || attacked == "��" || attacked == "��" || attacked == "����") ret = 2;
		else if (attacked == "����") ret = 0;
	}

	return ret;
}

void choose(CTrainer& trainer) //Ʈ���̳� ���ϸ� ����
{
	std::cout << "=====���ϸ� ���=====" << std::endl;
	std::cout << "1. ��ī��" << std::endl;
	std::cout << "2. �̻��ز�" << std::endl;
	std::cout << "3. �źϿ�" << std::endl;
	std::cout << "4. ���ڸ�" << std::endl;
	std::cout << "5. ������" << std::endl;
	std::cout << "6. �ս���" << std::endl;
	std::cout << "7. ������" << std::endl;
	std::cout << "8. ����" << std::endl;
	std::cout << "9. �ĵ�" << std::endl;
	std::cout << "10. ������" << std::endl;
	std::cout << "=====================" << std::endl << std::endl;

	int num[3];
	std::string str, temp[100];
	std::cout << "���ϴ� ���ϸ��� ������ �ּ���.(���ϴ� ���ϸ� �̸� ���� ���ڸ� �Է����ּ���)" << std::endl; //ù��° ���ϸ� ����
	std::cin.ignore(); //���ۺ���
	while (1)
	{
		bool getoutofwhile = false; //���ѹݺ� Ż�� �÷���
		std::getline(std::cin, str);

		int j = 0; //temp ���ڿ� �ִ� ����
		for (int i = 0; i < 100; i++) temp[i] = ""; //���ڿ� �迭 �ʱ�ȭ
		for (int i = 0; i < str.size(); i++) //���� �������� �Է¹��� �� ����
		{
			if (str[i] == ' ') j++;
			else temp[j] += str[i];
		}

		bool point = false; //���� �ٸ� �����޽����� ���ÿ� ��µǴ� ��� ������ �÷���
		for (int i = 0; i <= j; i++) //�� �κ��� ���ڰ� 1�̻� 10 �������� üũ
		{
			//�߸��� �Է� : ���ڸ��� �̻�, 1�� �������� �ʴ� ���ڸ���, 10�� �ƴ� ���ڸ���, 1�̻� 9���ϰ� �ƴ� ���ڸ���
			if (temp[i].size() >= 3 || (temp[i].size() == 2 && !(temp[i][0] == '1' && temp[i][1] == '0')) || (temp[i].size() == 1 && !('1' <= temp[i][0] && temp[i][0] <= '9')))
			{
				std::cout << "�Է��Ͻ� ���ڵ� �� 1���� 10 ������ ���ڰ� �ƴ� �Է��� �����մϴ�. 3���� ���ڸ� �ٽ� �Է����ּ���." << std::endl;
				point = true;
				break;
			}
		}

		if (!point) //�� �κ��� ���ڰ� 1�̻� 10������ ���
		{
			if (j > 2) std::cout << "���ϸ��� 3�������� ���� ������ �� �����ϴ�. 3���� ���ڸ� �ٽ� �Է����ּ���." << std::endl;
			else if (j < 2) std::cout << "���ϸ��� 3�������� ���� ������ �� �����ϴ�. 3���� ���ڸ� �ٽ� �Է����ּ���." << std::endl;
			else //3���� ����
			{
				if (temp[0] != temp[1] && temp[0] != temp[2] && temp[1] != temp[2]) //��� ���� �ٸ� ���(�ߺ�x)
				{
					for (int k = 0; k < 3; k++)
					{
						if (temp[k].size() == 1) num[k] = (int)(temp[k][0] - '0'); //���ڸ����� ��� ����
						else num[k] = 10; //���ݱ��� ���� ���ڸ� ���� 10 ��
					}
					getoutofwhile = true;
				}
				else std::cout << "�ߺ� ������ �Ұ����մϴ�. 3���� ���ڸ� �ٽ� �Է����ּ���." << std::endl; //�ߺ��� ���ڰ� �����ϴ� ���
			}
		}

		if (getoutofwhile) break;
	}

	trainer.set_pokemons(num[0], num[1], num[2]); //Ʈ���̳� ���ϸ����� ����

	std::cout << "�޴��� ���ư��ϴ�..." << std::endl;
	Sleep(1000);
	system("cls");
}

void choose_rival(CRival& rival) //���̹� ���ϸ� ����
{
	int a, b, c;
	a = rand() % 10 + 1; //ù��° ���ϸ�
	while (1) //�ι�° ���ϸ�
	{
		b = rand() % 10 + 1;
		if (a != b) break; //�ߺ��̸� �ٽ�
	}
	while (1) //����° ���ϸ�
	{
		c = rand() % 10 + 1;
		if (a != c && b != c) break; //�ߺ��̸� �ٽ�
	}

	rival.set_pokemons(a, b, c); //���̹� ���ϸ����� ����
}

inline void gameexit() //��������
{
	std::cout << "������ �����մϴ�." << std::endl;
}

