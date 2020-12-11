#include "CTrainer.h"

void CTrainer::set_pokemons(int a, int b, int c) //포켓몬 정보 가져옴
{
	pokemons[0].set_all_init(a);
	pokemons[1].set_all_init(b);
	pokemons[2].set_all_init(c);
	isget = true;
}

void CTrainer::set_hp(double damage) //포켓몬 체력 변경
{
	pokemons[in_battle].set_hp(damage);
}

void CTrainer::set_knock_down() //전투불능 세팅
{
	pokemons[in_battle].set_knock_down();
}

std::string CTrainer::get_main_type() //포켓몬 메인 타입 가져옴
{
	return pokemons[in_battle].get_main_type();
}

std::string CTrainer::get_sub_type() //포켓몬 서브 타입 가져옴
{
	return pokemons[in_battle].get_sub_type();
}

int CTrainer::get_defense() //포켓몬 방어력 가져옴
{
	return pokemons[in_battle].get_defense();
}

double CTrainer::get_hp() //포켓몬 체력 가져옴
{
	return pokemons[in_battle].get_hp();
}

int CTrainer::get_speed() //포켓몬 스피드 리턴
{
	return pokemons[in_battle].get_speed();
}

std::string CTrainer::get_attack_type(int skill) //사용한 기술의 타입 리턴
{
	return pokemons[in_battle].get_skill_type(skill - 1);
}

int CTrainer::get_skill_damage(int skill) //사용한 기술의 대미지 리턴
{
	return pokemons[in_battle].get_skill_damage(skill - 1);
}

int CTrainer::get_attack() //포켓몬 공격력 리턴
{
	return pokemons[in_battle].get_attack();
}

int CTrainer::get_in_battle() //몇번째 포켓몬이 배틀 중인지 확인
{
	return in_battle;
}

bool CTrainer::check() //포켓몬 소유 여부 체크
{
	if (isget) return true;
	else return false;
}

void CTrainer::show_info() //포켓몬 정보 출력
{
	std::cout << "===내 포켓몬===" << std::endl;
	for (int i = 0; i < 3; i++) pokemons[i].show(); //각 포켓몬의 이름, 타입 출력
}

void CTrainer::show_battle_info() //배틀 중 포켓몬 정보 출력
{
	pokemons[in_battle].show_battle_info(0);
}

int CTrainer::battle() //포켓몬이 사용할 기술 선택
{
	std::cout << "1. " << pokemons[in_battle].get_skill_name(0) << std::endl;
	std::cout << "2. " << pokemons[in_battle].get_skill_name(1) << std::endl;
	
	int choice;
	while (1)
	{
		std::cin >> choice;
		if (choice == 1) //1번 기술 발동
		{
			std::cout << pokemons[in_battle].get_name() << "의 " << pokemons[in_battle].get_skill_name(0) << std::endl;
			return 1;
		}
		else if (choice == 2) //2번 기술 발동
		{
			std::cout << pokemons[in_battle].get_name() << "의 " << pokemons[in_battle].get_skill_name(1) << std::endl;
			return 2;
		}

		else //예외 처리
		{
			std::cout << "잘못된 입력입니다. 1 또는 2를 입력해주세요." << std::endl;
		}
	}
}

int CTrainer::change() //포켓몬 교체
{
	std::cout << "===내 포켓몬===" << std::endl;
	std::cout << "1. " << pokemons[0].get_name() << std::endl;
	std::cout << "2. " << pokemons[1].get_name() << std::endl;
	std::cout << "3. " << pokemons[2].get_name() << std::endl;
	std::cout << "==============" << std::endl;
	std::cout << "교체할 포켓몬을 선택해주세요.(0은 뒤로가기)" << std::endl;
	int n;
	while (1)
	{
		std::cin >> n;
		if (n < 0 || n > 3) std::cout << "0, 1, 2, 3 중에서 입력해주세요." << std::endl;
		else if (n == 0) //뒤로가기
		{
			return 0;
		}
		else if (n-1 == in_battle) std::cout << "배틀 중인 포켓몬을 선택하셨습니다. 다시 입력해주세요." << std::endl; //배틀 중 포켓몬 선택 불가
		else if (pokemons[n-1].get_knock_down() == true) std::cout << "전투 불능인 포켓몬을 선택하셨습니다. 다시 입력해주세요." << std::endl; //전투 불능인 포켓몬 선택 불가
		else
		{
			in_battle = n-1; //포켓몬 교체
			std::cout << "가라 " << pokemons[in_battle].get_name() << std::endl;
			return 1; //턴종료
		}
	}
}

void CTrainer::change_v2() //전투불능 상황 포켓몬 교체
{
	std::cout << "===내 포켓몬===" << std::endl;
	std::cout << "1. " << pokemons[0].get_name() << std::endl;
	std::cout << "2. " << pokemons[1].get_name() << std::endl;
	std::cout << "3. " << pokemons[2].get_name() << std::endl;
	std::cout << "==============" << std::endl;
	std::cout << "교체할 포켓몬을 선택해주세요." << std::endl;
	int n;
	while (1)
	{
		std::cin >> n;
		if (n < 1 || n > 3) std::cout << "1, 2, 3 중에서 입력해주세요." << std::endl;
		else if (n-1 == in_battle || pokemons[n-1].get_knock_down() == true) std::cout << "전투 불능인 포켓몬을 선택하셨습니다. 다시 입력해주세요." << std::endl; //전투 불능인(+배틀중인) 포켓몬 선택 불가
		else
		{
			in_battle = n - 1; //포켓몬 교체
			std::cout << "가라 " << pokemons[in_battle].get_name() << std::endl;
			break;
		}
	}
}

int CTrainer::isover() //시합 끝났는지 체크
{
	if (pokemons[0].get_knock_down() == true && pokemons[1].get_knock_down() == true && pokemons[2].get_knock_down() == true) return 1; //모든 포켓몬이 전투 불능
	else return 0;
}

void CTrainer::init() //트레이너 정보 초기화
{
	isget = false;
	in_battle = 0;
}

int CTrainer::give_up() //항복
{
	std::cout << "항복으로 대전이 종료되었습니다." << std::endl;
	std::cout << "메뉴로 돌아갑니다..." << std::endl;
	return 100;
}

