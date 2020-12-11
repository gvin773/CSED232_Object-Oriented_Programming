#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <utility>

class list
{
public: //CPokemon������ �����ο� ������ ����
	std::string name[10] = { "��ī��", "�̻��ز�", "�źϿ�", "���ڸ�", "������", "�ս���", "������", "����", "�ĵ�", "������" };
	std::string main_type[10] = { "����", "Ǯ", "��", "��", "�븻", "����", "����", "����Ʈ", "������", "�巡��" };
	std::string sub_type[10] = { " ", "��", " ", "����", "����", "��", "����", "��", " ", "����" };
	int hp[10] = { 160, 250, 240, 200, 170, 190, 140, 150, 150, 210 };
	int attack[10] = { 80, 100, 95, 105, 90, 75, 70, 105, 105, 110 };
	int defense[10] = { 70, 110, 90, 70, 60, 100, 50, 55, 55, 85 };
	int speed[10] = { 95, 70, 75, 90, 95, 50, 60, 110, 115, 100 };
	std::pair<std::string, int> skills[13] = { {"����", 95}, {"Ǯ", 110}, {"��", 120}, {"��", 95}, {"����", 80}, {"����", 75}, {"�巡��", 120}, {"������", 90}, {"��", 75}, {"����Ʈ", 85}, {"�븻", 50}, {"����", 80}, {"��", 100} };
	std::string skill_name[13] = { "10����Ʈ", "�ֶ��", "���̵������", "ȭ�����", "����ġ��", "����ũ�ν�", "����", "������Ű�׽ý�", "ũ�ν�������", "�����캼", "�����ġ��", "�������", "����" };
};

#endif

