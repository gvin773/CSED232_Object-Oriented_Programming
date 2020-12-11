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
	//������� ���ϸ� ������
	list l; //���ϸ� ����Ʈ

public:
	void set_all_init(int index); //���ϸ� ������ �ʱ�ȭ
	void set_hp(double damage); //ü�� ����
	void set_knock_down(); //�����Ҵ� ����

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
	//�� ��������� �����ϴ� get

	void show(); //���ϸ� �̸�, Ÿ�� ���
	void show_battle_info(int i); //��Ʋ �� ���ϸ� ���� ���
};

#endif

