#include "CRival.h"

void CRival::set_pokemons(int a, int b, int c) //포켓몬 정보 가져옴
{
	pokemons[0].set_all_init(a);
	pokemons[1].set_all_init(b);
	pokemons[2].set_all_init(c);
}

void CRival::set_hp(double damage) //포켓몬 체력 변경
{
	pokemons[in_battle].set_hp(damage);
}

void CRival::set_knock_down() //전투불능 세팅
{
	pokemons[in_battle].set_knock_down();
}

std::string CRival::get_main_type() //포켓몬 메인 타입 가져옴
{
	return pokemons[in_battle].get_main_type();
}

std::string CRival::get_sub_type() //포켓몬 서브 타입 가져옴
{
	return pokemons[in_battle].get_sub_type();
}

int CRival::get_defense() //포켓몬 방어력 가져옴
{
	return pokemons[in_battle].get_defense();
}

double CRival::get_hp() //포켓몬 체력 가져옴
{
	return pokemons[in_battle].get_hp();
}

int CRival::get_speed() //포켓몬 스피드 리턴
{
	return pokemons[in_battle].get_speed();
}

std::string CRival::get_attack_type(int skill) //사용한 기술의 타입 리턴
{
	return pokemons[in_battle].get_skill_type(skill - 1);
}

int CRival::get_skill_damage(int skill) //사용한 기술의 대미지 리턴
{
	return pokemons[in_battle].get_skill_damage(skill - 1);
}

int CRival::get_attack() //포켓몬 공격력 리턴
{
	return pokemons[in_battle].get_attack();
}

int CRival::get_in_battle() //몇번째 포켓몬이 배틀 중인지 확인
{
	return in_battle;
}

int CRival::battle() //포켓몬이 사용할 기술 선택
{
	int choice = rand() % 2 + 1;
	if (choice == 1)
	{
		std::cout << "상대 " << pokemons[in_battle].get_name() << "의 " << pokemons[in_battle].get_skill_name(0) << std::endl;
		return 1;
	}
	else if (choice == 2)
	{
		std::cout << "상대 " << pokemons[in_battle].get_name() << "의 " << pokemons[in_battle].get_skill_name(1) << std::endl;
		return 2;
	}
}

void CRival::show_info() //포켓몬 정보 출력
{
	std::cout << "===상대 포켓몬===" << std::endl;
	for (int i = 0; i < 3; i++) pokemons[i].show(); //각 포켓몬의 이름, 타입 출력
}

void CRival::show_battle_info() //배틀 중 포켓몬 정보 출력
{
	pokemons[in_battle].show_battle_info(1);
}

void CRival::init() //라이벌 정보 초기화
{
	in_battle = 0;
}

void CRival::next() //다음 포켓몬으로 변경
{
	in_battle++;
}

