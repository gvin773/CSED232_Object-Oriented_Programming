#ifndef CPOKEMON_H_
#define CPOKEMON_H_

#include "list.h"
#include <iostream>

class CPokemon
{
private:
	std::string name;
	std::string main_type;
	std::string sub_type;
	double hp;
	int attack;
	int defense;
	int speed;
	std::pair<std::string, int> skills[2];
	std::string skill_name[2];
	bool knock_down;
	//여기까지 포켓몬 데이터
	list l; //포켓몬 리스트

public:
	void set_all_init(int index); //포켓몬 데이터 초기화
	void set_hp(double damage); //체력 세팅
	void set_knock_down(); //전투불능 세팅

	std::string get_name();
	std::string get_main_type();
	std::string get_sub_type();
	double get_hp();
	int get_attack();
	int get_defense();
	int get_speed();
	std::string get_skill_type(int i);
	int get_skill_damage(int i);
	std::string get_skill_name(int i);
	bool get_knock_down();
	//각 멤버변수에 접근하는 get

	void show(); //포켓몬 이름, 타입 출력
	void show_battle_info(int i); //배틀 중 포켓몬 정보 출력
};

#endif

