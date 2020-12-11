#include "CRival.h"

void CRival::set_pokemons(int a, int b, int c) //���ϸ� ���� ������
{
	pokemons[0].set_all_init(a);
	pokemons[1].set_all_init(b);
	pokemons[2].set_all_init(c);
}

void CRival::set_hp(double damage) //���ϸ� ü�� ����
{
	pokemons[in_battle].set_hp(damage);
}

void CRival::set_knock_down() //�����Ҵ� ����
{
	pokemons[in_battle].set_knock_down();
}

std::string CRival::get_main_type() //���ϸ� ���� Ÿ�� ������
{
	return pokemons[in_battle].get_main_type();
}

std::string CRival::get_sub_type() //���ϸ� ���� Ÿ�� ������
{
	return pokemons[in_battle].get_sub_type();
}

int CRival::get_defense() //���ϸ� ���� ������
{
	return pokemons[in_battle].get_defense();
}

double CRival::get_hp() //���ϸ� ü�� ������
{
	return pokemons[in_battle].get_hp();
}

int CRival::get_speed() //���ϸ� ���ǵ� ����
{
	return pokemons[in_battle].get_speed();
}

std::string CRival::get_attack_type(int skill) //����� ����� Ÿ�� ����
{
	return pokemons[in_battle].get_skill_type(skill - 1);
}

int CRival::get_skill_damage(int skill) //����� ����� ����� ����
{
	return pokemons[in_battle].get_skill_damage(skill - 1);
}

int CRival::get_attack() //���ϸ� ���ݷ� ����
{
	return pokemons[in_battle].get_attack();
}

int CRival::get_in_battle() //���° ���ϸ��� ��Ʋ ������ Ȯ��
{
	return in_battle;
}

int CRival::battle() //���ϸ��� ����� ��� ����
{
	int choice = rand() % 2 + 1;
	if (choice == 1)
	{
		std::cout << "��� " << pokemons[in_battle].get_name() << "�� " << pokemons[in_battle].get_skill_name(0) << std::endl;
		return 1;
	}
	else if (choice == 2)
	{
		std::cout << "��� " << pokemons[in_battle].get_name() << "�� " << pokemons[in_battle].get_skill_name(1) << std::endl;
		return 2;
	}
}

void CRival::show_info() //���ϸ� ���� ���
{
	std::cout << "===��� ���ϸ�===" << std::endl;
	for (int i = 0; i < 3; i++) pokemons[i].show(); //�� ���ϸ��� �̸�, Ÿ�� ���
}

void CRival::show_battle_info() //��Ʋ �� ���ϸ� ���� ���
{
	pokemons[in_battle].show_battle_info(1);
}

void CRival::init() //���̹� ���� �ʱ�ȭ
{
	in_battle = 0;
}

void CRival::next() //���� ���ϸ����� ����
{
	in_battle++;
}

