#include "CTrainer.h"

void CTrainer::set_pokemons(int a, int b, int c) //���ϸ� ���� ������
{
	pokemons[0].set_all_init(a);
	pokemons[1].set_all_init(b);
	pokemons[2].set_all_init(c);
	isget = true;
}

void CTrainer::set_hp(double damage) //���ϸ� ü�� ����
{
	pokemons[in_battle].set_hp(damage);
}

void CTrainer::set_knock_down() //�����Ҵ� ����
{
	pokemons[in_battle].set_knock_down();
}

std::string CTrainer::get_main_type() //���ϸ� ���� Ÿ�� ������
{
	return pokemons[in_battle].get_main_type();
}

std::string CTrainer::get_sub_type() //���ϸ� ���� Ÿ�� ������
{
	return pokemons[in_battle].get_sub_type();
}

int CTrainer::get_defense() //���ϸ� ���� ������
{
	return pokemons[in_battle].get_defense();
}

double CTrainer::get_hp() //���ϸ� ü�� ������
{
	return pokemons[in_battle].get_hp();
}

int CTrainer::get_speed() //���ϸ� ���ǵ� ����
{
	return pokemons[in_battle].get_speed();
}

std::string CTrainer::get_attack_type(int skill) //����� ����� Ÿ�� ����
{
	return pokemons[in_battle].get_skill_type(skill - 1);
}

int CTrainer::get_skill_damage(int skill) //����� ����� ����� ����
{
	return pokemons[in_battle].get_skill_damage(skill - 1);
}

int CTrainer::get_attack() //���ϸ� ���ݷ� ����
{
	return pokemons[in_battle].get_attack();
}

int CTrainer::get_in_battle() //���° ���ϸ��� ��Ʋ ������ Ȯ��
{
	return in_battle;
}

bool CTrainer::check() //���ϸ� ���� ���� üũ
{
	if (isget) return true;
	else return false;
}

void CTrainer::show_info() //���ϸ� ���� ���
{
	std::cout << "===�� ���ϸ�===" << std::endl;
	for (int i = 0; i < 3; i++) pokemons[i].show(); //�� ���ϸ��� �̸�, Ÿ�� ���
}

void CTrainer::show_battle_info() //��Ʋ �� ���ϸ� ���� ���
{
	pokemons[in_battle].show_battle_info(0);
}

int CTrainer::battle() //���ϸ��� ����� ��� ����
{
	std::cout << "1. " << pokemons[in_battle].get_skill_name(0) << std::endl;
	std::cout << "2. " << pokemons[in_battle].get_skill_name(1) << std::endl;
	
	int choice;
	while (1)
	{
		std::cin >> choice;
		if (choice == 1) //1�� ��� �ߵ�
		{
			std::cout << pokemons[in_battle].get_name() << "�� " << pokemons[in_battle].get_skill_name(0) << std::endl;
			return 1;
		}
		else if (choice == 2) //2�� ��� �ߵ�
		{
			std::cout << pokemons[in_battle].get_name() << "�� " << pokemons[in_battle].get_skill_name(1) << std::endl;
			return 2;
		}

		else //���� ó��
		{
			std::cout << "�߸��� �Է��Դϴ�. 1 �Ǵ� 2�� �Է����ּ���." << std::endl;
		}
	}
}

int CTrainer::change() //���ϸ� ��ü
{
	std::cout << "===�� ���ϸ�===" << std::endl;
	std::cout << "1. " << pokemons[0].get_name() << std::endl;
	std::cout << "2. " << pokemons[1].get_name() << std::endl;
	std::cout << "3. " << pokemons[2].get_name() << std::endl;
	std::cout << "==============" << std::endl;
	std::cout << "��ü�� ���ϸ��� �������ּ���.(0�� �ڷΰ���)" << std::endl;
	int n;
	while (1)
	{
		std::cin >> n;
		if (n < 0 || n > 3) std::cout << "0, 1, 2, 3 �߿��� �Է����ּ���." << std::endl;
		else if (n == 0) //�ڷΰ���
		{
			return 0;
		}
		else if (n-1 == in_battle) std::cout << "��Ʋ ���� ���ϸ��� �����ϼ̽��ϴ�. �ٽ� �Է����ּ���." << std::endl; //��Ʋ �� ���ϸ� ���� �Ұ�
		else if (pokemons[n-1].get_knock_down() == true) std::cout << "���� �Ҵ��� ���ϸ��� �����ϼ̽��ϴ�. �ٽ� �Է����ּ���." << std::endl; //���� �Ҵ��� ���ϸ� ���� �Ұ�
		else
		{
			in_battle = n-1; //���ϸ� ��ü
			std::cout << "���� " << pokemons[in_battle].get_name() << std::endl;
			return 1; //������
		}
	}
}

void CTrainer::change_v2() //�����Ҵ� ��Ȳ ���ϸ� ��ü
{
	std::cout << "===�� ���ϸ�===" << std::endl;
	std::cout << "1. " << pokemons[0].get_name() << std::endl;
	std::cout << "2. " << pokemons[1].get_name() << std::endl;
	std::cout << "3. " << pokemons[2].get_name() << std::endl;
	std::cout << "==============" << std::endl;
	std::cout << "��ü�� ���ϸ��� �������ּ���." << std::endl;
	int n;
	while (1)
	{
		std::cin >> n;
		if (n < 1 || n > 3) std::cout << "1, 2, 3 �߿��� �Է����ּ���." << std::endl;
		else if (n-1 == in_battle || pokemons[n-1].get_knock_down() == true) std::cout << "���� �Ҵ��� ���ϸ��� �����ϼ̽��ϴ�. �ٽ� �Է����ּ���." << std::endl; //���� �Ҵ���(+��Ʋ����) ���ϸ� ���� �Ұ�
		else
		{
			in_battle = n - 1; //���ϸ� ��ü
			std::cout << "���� " << pokemons[in_battle].get_name() << std::endl;
			break;
		}
	}
}

int CTrainer::isover() //���� �������� üũ
{
	if (pokemons[0].get_knock_down() == true && pokemons[1].get_knock_down() == true && pokemons[2].get_knock_down() == true) return 1; //��� ���ϸ��� ���� �Ҵ�
	else return 0;
}

void CTrainer::init() //Ʈ���̳� ���� �ʱ�ȭ
{
	isget = false;
	in_battle = 0;
}

int CTrainer::give_up() //�׺�
{
	std::cout << "�׺����� ������ ����Ǿ����ϴ�." << std::endl;
	std::cout << "�޴��� ���ư��ϴ�..." << std::endl;
	return 100;
}

