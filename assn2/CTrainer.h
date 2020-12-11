#ifndef CTRAINER_H_
#define CTRAINER_H_

#include "CPokemon.h"

class CTrainer
{
private:
	CPokemon pokemons[3]; //���ϸ� ������
	int in_battle = 0; //���� ��Ʋ�� ���� �ִ� ���ϸ�
	bool isget = false; //���ϸ� �����ߴ��� Ȯ���ϴ� ����

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
	bool check(); //���ϸ� ���� ���� üũ

	void show_info(); //���ϸ� ���� ���
	void show_battle_info(); //��Ʋ �� ���ϸ� ���� ���

	int battle(); //���ϸ��� ����� ��� ����

	int change(); //���ϸ� ��ü
	void change_v2(); //�����Ҵ� ��Ȳ ���ϸ� ��ü
	
	int isover(); //���� �������� üũ
	void init(); //Ʈ���̳� ���� �ʱ�ȭ

	int give_up(); //�׺�
};

#endif

