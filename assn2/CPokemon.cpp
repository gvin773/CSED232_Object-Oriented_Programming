#include "CPokemon.h"

void CPokemon::set_all_init(int index) //포켓몬 데이터 초기화
{
	name = l.name[index-1]; //데이터는 0부터 시작
	main_type = l.main_type[index-1];
	sub_type = l.sub_type[index-1];
	hp = l.hp[index-1];
	attack = l.attack[index-1];
	defense = l.defense[index-1];
	speed = l.speed[index-1];
	for(int i = 0; i < 13; i++) //타입과 일치하는 첫번째 기술
	{
		if (main_type == l.skills[i].first) //메인타입과 일치
		{
			skills[0].first = main_type;
			skills[0].second = l.skills[i].second;
			skill_name[0] = l.skill_name[i];
			break;
		}
	}
	while (1) //타입과 다른 두번째 기술
	{
		int i = rand() % 13;
		if (main_type == l.skills[i].first) continue; //두번째 기술과 첫번째 기술이 중복이면 안되므로
		skills[1].first = l.skills[i].first;
		skills[1].second = l.skills[i].second;
		skill_name[1] = l.skill_name[i];
		break;
	}
	knock_down = false;
}

void CPokemon::set_hp(double damage) //체력 세팅
{
	hp += damage;
	if (hp < 0) hp = 0;
}

void CPokemon::set_knock_down() //전투불능 세팅
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

void CPokemon::show() //포켓몬 이름, 타입 출력
{
	std::cout << name << ' ' << main_type << ' ' << sub_type << std::endl;
}

void CPokemon::show_battle_info(int i) //배틀 중 포켓몬 정보 출력
{
	if(i == 0) std::cout << "나 : " << name << ' ' << hp << std::endl;
	else std::cout << "상대 : " << name << ' ' << hp << std::endl;
}

