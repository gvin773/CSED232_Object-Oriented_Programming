#ifndef CRIVAL_H_
#define CRIVAL_H_

#include "CPokemon.h"

class CRival
{
private:
	CPokemon pokemons[3]; //���ϸ� ������
	int in_battle = 0; //���� ��Ʋ�� ���� �ִ� ���ϸ�

public:
	void set_pokemons(int a, int b, int c); //���ϸ� ���� ������
	void set_hp(double damage); //���ϸ� ü�� ����
	void set_knock_down(); //�����Ҵ� ����

	std::string get_main_type(); //���ϸ� ���� Ÿ�� ������
	std::string get_sub_type(); //���ϸ� ���� Ÿ�� ������
	int get_defense(); //���ϸ� ���� ������
	double get_hp(); //���ϸ� ü�� ������
	int get_speed(); //���ϸ� ���ǵ� ����
	std::string get_attack_type(int skill); //����� ����� Ÿ�� ����
	int get_skill_damage(int skill); //����� ����� ����� ����
	int get_attack(); //���ϸ� ���ݷ� ����
	int get_in_battle(); //���° ���ϸ��� ��Ʋ ������ Ȯ��

	int battle(); //���ϸ��� ����� ��� ����

	void show_info(); //���ϸ� ���� ���
	void show_battle_info(); //��Ʋ �� ���ϸ� ���� ���

	void init(); //���̹� ���� �ʱ�ȭ
	void next(); //���� ���ϸ����� ����
};

#endif

