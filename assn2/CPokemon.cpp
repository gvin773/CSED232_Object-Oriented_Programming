#include "CPokemon.h"

void CPokemon::set_all_init(int index) //���ϸ� ������ �ʱ�ȭ
{
	name = l.name[index-1]; //�����ʹ� 0���� ����
	main_type = l.main_type[index-1];
	sub_type = l.sub_type[index-1];
	hp = l.hp[index-1];
	attack = l.attack[index-1];
	defense = l.defense[index-1];
	speed = l.speed[index-1];
	for(int i = 0; i < 13; i++) //Ÿ�԰� ��ġ�ϴ� ù��° ���
	{
		if (main_type == l.skills[i].first) //����Ÿ�԰� ��ġ
		{
			skills[0].first = main_type;
			skills[0].second = l.skills[i].second;
			skill_name[0] = l.skill_name[i];
			break;
		}
	}
	while (1) //Ÿ�԰� �ٸ� �ι�° ���
	{
		int i = rand() % 13;
		if (main_type == l.skills[i].first) continue; //�ι�° ����� ù��° ����� �ߺ��̸� �ȵǹǷ�
		skills[1].first = l.skills[i].first;
		skills[1].second = l.skills[i].second;
		skill_name[1] = l.skill_name[i];
		break;
	}
	knock_down = false;
}

void CPokemon::set_hp(double damage) //ü�� ����
{
	hp += damage;
	if (hp < 0) hp = 0;
}

void CPokemon::set_knock_down() //�����Ҵ� ����
{
	knock_down = true;
}

std::string CPokemon::get_name()
{
	return name;
}

std::string CPokemon::get_main_type()
{
	return main_type;
}

std::string CPokemon::get_sub_type()
{
	return sub_type;
}

double CPokemon::get_hp()
{
	return hp;
}

int CPokemon::get_attack()
{
	return attack;
}

int CPokemon::get_defense()
{
	return defense;
}

int CPokemon::get_speed()
{
	return speed;
}

std::string CPokemon::get_skill_type(int i)
{
	return skills[i].first;
}

int CPokemon::get_skill_damage(int i)
{
	return skills[i].second;
}

std::string CPokemon::get_skill_name(int i)
{
	return skill_name[i];
}

bool CPokemon::get_knock_down()
{
	return knock_down;
}

void CPokemon::show() //���ϸ� �̸�, Ÿ�� ���
{
	std::cout << name << ' ' << main_type << ' ' << sub_type << std::endl;
}

void CPokemon::show_battle_info(int i) //��Ʋ �� ���ϸ� ���� ���
{
	if(i == 0) std::cout << "�� : " << name << ' ' << hp << std::endl;
	else std::cout << "��� : " << name << ' ' << hp << std::endl;
}

