#ifndef CRIVAL_H_
#define CRIVAL_H_

#include "CPokemon.h"

class CRival
{
private:
	CPokemon pokemons[3]; //포켓몬 데이터
	int in_battle = 0; //현재 배틀에 나가 있는 포켓몬

public:
	void set_pokemons(int a, int b, int c); //포켓몬 정보 가져옴
	void set_hp(double damage); //포켓몬 체력 변경
	void set_knock_down(); //전투불능 세팅

	std::string get_main_type(); //포켓몬 메인 타입 가져옴
	std::string get_sub_type(); //포켓몬 서브 타입 가져옴
	int get_defense(); //포켓몬 방어력 가져옴
	double get_hp(); //포켓몬 체력 가져옴
	int get_speed(); //포켓몬 스피드 리턴
	std::string get_attack_type(int skill); //사용한 기술의 타입 리턴
	int get_skill_damage(int skill); //사용한 기술의 대미지 리턴
	int get_attack(); //포켓몬 공격력 리턴
	int get_in_battle(); //몇번째 포켓몬이 배틀 중인지 확인

	int battle(); //포켓몬이 사용할 기술 선택

	void show_info(); //포켓몬 정보 출력
	void show_battle_info(); //배틀 중 포켓몬 정보 출력

	void init(); //라이벌 정보 초기화
	void next(); //다음 포켓몬으로 변경
};

#endif

