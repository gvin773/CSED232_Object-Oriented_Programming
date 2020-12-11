#include <windows.h>
#include <ctime>
#include "CTrainer.h"
#include "CRival.h"

void ready(CTrainer& trainer, CRival& rival); //배틀준비
void fight(CTrainer& trainer, CRival& rival); //배틀진행
int turn_trainer(CTrainer& trainer, CRival& rival); //트레이너 턴
int turn_rival(CTrainer& trainer, CRival& rival); //라이벌 턴
void show_board(CTrainer& trainer, CRival& rival); //배틀 진행 중 포켓몬 이름, 체력 표시
double compatibility(std::string attack, std::string attacked); //상성 체크

void choose(CTrainer& trainer); //트레이너 포켓몬 선택
void choose_rival(CRival& rival); //라이벌 포켓몬 선택

inline void gameexit(); //게임종료

int main()
{
	srand((unsigned int)time(NULL)); //시드랜덤

	CTrainer trainer;
	CRival rival;

	while (1)
	{
		system("cls");
		std::cout << "1. 배틀하기" << std::endl;
		std::cout << "2. 포켓몬 선택" << std::endl;
		std::cout << "3. 종료" << std::endl;

		int n;
		std::cin >> n; //메뉴입력
		system("cls");
		if (n == 1) //배틀
		{
			if (!trainer.check()) //포켓몬 선택을 하지 않았으면
			{
				std::cout << "모든 포켓몬이 선택되지 않았습니다. 먼저 포켓몬을 선택해 주세요." << std::endl;
				std::cout << "메뉴로 돌아갑니다..." << std::endl;
				Sleep(1000);
				continue;
			}
			ready(trainer, rival); //배틀준비
			fight(trainer, rival); //배틀진행
			trainer.init(); //트레이너 정보 초기화
			rival.init(); //라이벌 정보 초기화
		}
		else if (n == 2) choose(trainer); //포켓몬선택
		else if (n == 3) break; //종료
		else std::cout << "1, 2, 3 중 하나의 숫자를 입력해주세요!" << std::endl; //예외처리
		Sleep(1000);
	}

	gameexit(); //게임종료메시지
	return 0;
}

void ready(CTrainer& trainer, CRival& rival) //배틀준비
{
	choose_rival(rival); //라이벌 포켓몬 선택

	std::cout << "규빈스타디움에 오신 것을 환영합니다." << std::endl;
	trainer.show_info();
	std::cout << std::endl;
	rival.show_info();
	std::cout << std::endl << "잠시 후 배틀이 시작됩니다.";
	Sleep(3000);
	system("cls");
}

void fight(CTrainer& trainer, CRival& rival) //배틀진행
{
	while (1)
	{
		if (trainer.get_speed() >= rival.get_speed()) //트레이너 먼저 시작
		{
			while (1)
			{
				int tt = turn_trainer(trainer, rival);
				if (tt == 1) break; //상대포켓몬이 쓰러지면 선후공 다시 정해야함
				else if (tt == 100) return; //시합이 종료되었으므로 메뉴로 돌아감
				Sleep(1500);
				int tr = turn_rival(trainer, rival);
				if (tr == 1) break; //내 포켓몬이 쓰러지면 선후공 다시 정해야함
				else if (tr == 100) return; //시합이 종료되었으므로 메뉴로 돌아감
				Sleep(1500);
			}
		}

		else //라이벌 먼저 시작
		{
			while (1)
			{
				int tr = turn_rival(trainer, rival);
				if (tr == 1) break; //내 포켓몬이 쓰러지면 선후공 다시 정해야함
				else if (tr == 100) return; //시합이 종료되었으므로 메뉴로 돌아감
				Sleep(1500);
				int tt = turn_trainer(trainer, rival);
				if (tt == 1) break; //상대포켓몬이 쓰러지면 선후강 다시 정해야함
				else if (tt == 100) return; //시합이 종료되었으므로 메뉴로 돌아감
				Sleep(1500);
			}
		}
	}
}

int turn_trainer(CTrainer& trainer, CRival& rival) //트레이너 턴
{
	system("cls");
	show_board(trainer, rival);
	std::cout << "내 턴이 되었다! 무엇을 할까?" << std::endl;
	while (1)
	{
		std::cout << "1. 싸운다. " << "2. 포켓몬 " << "3. 항복" << std::endl;
		int choice;
		std::cin >> choice;

		if (choice == 1) //기술 선택
		{
			double mul = 0; //배율
			int skill = trainer.battle(); //기술 선택
			if (trainer.get_attack_type(skill) == trainer.get_main_type() || trainer.get_attack_type(skill) == trainer.get_sub_type()) mul = 1.5; //자속보정
			else mul = 1; //기본배율
			mul *= compatibility(trainer.get_attack_type(skill), rival.get_main_type());
			mul *= compatibility(trainer.get_attack_type(skill), rival.get_sub_type()); //최종 배율 설정 완료

			double damage = 0; //대미지
			if (mul != 0) //배율이 0이면 대미지 0
			{
				damage = (double)rival.get_defense() - ((double)trainer.get_attack() + mul * (double)trainer.get_skill_damage(skill)); //대미지 계산
				if (damage > 0) damage = -1; //대미지 계산
			}

			rival.set_hp(damage); //체력 변경
			Sleep(2000);
			system("cls");
			show_board(trainer, rival); //변경된 체력 반영
			if (damage == 0) std::cout << "효과가 없는 것 같다..." << std::endl;
			else if (mul <= 0.5) std::cout << "효과가 별로인 듯 하다..." << std::endl;
			else if (mul >= 2) std::cout << "효과가 굉장했다!" << std::endl;
			else std::cout << "효과가 평범했다." << std::endl;

			if (rival.get_hp() == 0) //상대 포켓몬이 쓰러진 경우
			{
				std::cout << "상대 포켓몬이 쓰러졌다!" << std::endl;
				Sleep(1500);
				rival.set_knock_down(); //knock_down 반영
				rival.next(); //지금 포켓몬이 전투불능 상태이면 다음 포켓몬으로 변경
				if (rival.get_in_battle() >= 3) //트레이너 승리 게임 종료
				{
					std::cout << "상대 포켓몬이 모두 쓰러졌다!" << std::endl;
					std::cout << "*****승리*****" << std::endl;
					std::cout << "3초 뒤 메뉴로 돌아갑니다..." << std::endl;
					Sleep(3000);
					return 100; //시합종료
				}

				return 1;
			}

			break;
		}

		else if (choice == 2) //포켓몬 교체
		{
			if (trainer.change()) break; //뒤로가기가 아니면 턴종료
			system("cls");
			show_board(trainer, rival);
		}

		else if (choice == 3) //항복 -> 시합종료
		{
			int ret = trainer.give_up();
			Sleep(1000);
			return ret; //시합종료
		}

		else //잘못된 입력
		{
			system("cls");
			std::cout << "잘못된 입력입니다. 1, 2, 3 중 하나의 숫자를 입력해주세요." << std::endl;
			show_board(trainer, rival);
			continue;
		}
	}

	return 0;
}

int turn_rival(CTrainer& trainer, CRival& rival) //라이벌 턴
{
	system("cls");
	show_board(trainer, rival);
	std::cout << "상대 턴이 되었다!" << std::endl;
	Sleep(1500);

	double mul = 0; //배율
	int skill = rival.battle(); //상대의 기술 선택
	if (rival.get_attack_type(skill) == rival.get_main_type() || rival.get_attack_type(skill) == rival.get_sub_type()) mul = 1.5; //자속보정
	else mul = 1; //기본배율
	mul *= compatibility(rival.get_attack_type(skill), trainer.get_main_type());
	mul *= compatibility(rival.get_attack_type(skill), trainer.get_sub_type()); //최종 배율 설정 완료

	double damage = 0; //대미지
	if (mul != 0) //배율이 0이면 대미지 0
	{
		damage = (double)trainer.get_defense() - ((double)rival.get_attack() + mul * (double)rival.get_skill_damage(skill)); //대미지 계산
		if (damage > 0) damage = -1; //대미지 계산
	}

	trainer.set_hp(damage); //체력 변경
	Sleep(2000);
	system("cls");
	show_board(trainer, rival); //변경된 체력 반영
	if (damage == 0) std::cout << "효과가 없는 것 같다..." << std::endl;
	else if (mul <= 0.5) std::cout << "효과가 별로인 듯 하다..." << std::endl;
	else if (mul >= 2) std::cout << "효과가 굉장했다!" << std::endl;
	else std::cout << "효과가 평범했다." << std::endl;

	if (trainer.get_hp() == 0) //지금 포켓몬이 전투불능 상태이면
	{
		trainer.set_knock_down(); //knock_down 반영
		if (!trainer.isover()) //교체가능한 포켓몬이 있는 경우
		{
			std::cout << "내 포켓몬이 쓰러졌다!" << std::endl;
			Sleep(1500);
			trainer.change_v2(); //모든 포켓몬이 전투불능 상태가 아니면 다른 포켓몬으로 변경
			return 1;
		}
		else //교체가능한 포켓몬 없음 ; 라이벌 승리 게임 종료
		{
			std::cout << "내 포켓몬이 모두 쓰러졌다!" << std::endl;
			std::cout << "*****패배*****" << std::endl;
			std::cout << "3초 뒤 메뉴로 돌아갑니다..." << std::endl;
			Sleep(3000);
			return 100; //시합종료
		}
	}

	return 0;
}

void show_board(CTrainer& trainer, CRival& rival) //배틀 진행 중 포켓몬 이름, 체력 표시
{
	trainer.show_battle_info();
	rival.show_battle_info();
}

double compatibility(std::string attack, std::string attacked) //상성 체크
{
	double ret = 1; //상성에 의한 배율
	if (attack == "전기")
	{
		if (attacked == "전기" || attacked == "풀" || attacked == "드래곤") ret = 0.5;
		else if (attacked == "물" || attacked == "비행") ret = 2;
		else if (attacked == "땅") ret = 0;
	}
	else if (attack == "풀")
	{
		if (attacked == "풀" || attacked == "불" || attacked == "비행" || attacked == "벌레" || attacked == "드래곤" || attacked == "독") ret = 0.5;
		else if (attacked == "물" || attacked == "바위" || attacked == "바람") ret = 2;
	}
	else if (attack == "물")
	{
		if (attacked == "풀" || attacked == "물" || attacked == "드래곤") ret = 0.5;
		else if (attacked == "불" || attacked == "바위" || attacked == "땅") ret = 2;
	}
	else if (attack == "불")
	{
		if (attacked == "물" || attacked == "불" || attacked == "드래곤" || attacked == "바위") ret = 0.5;
		else if (attacked == "풀" || attacked == "벌레") ret = 2;
	}
	else if (attack == "비행")
	{
		if (attacked == "전기" || attacked == "바위") ret = 0.5;
		else if (attacked == "풀" || attacked == "벌레") ret = 2;
	}
	else if (attack == "벌레")
	{
		if (attacked == "불" || attacked == "비행" || attacked == "독" || attacked == "고스트") ret = 0.5;
		else if (attacked == "풀" || attacked == "에스퍼") ret = 2;
	}
	else if (attack == "드래곤")
	{
		if (attacked == "드래곤") ret = 2;
	}
	else if (attack == "에스퍼")
	{
		if (attacked == "에스퍼") ret = 0.5;
		else if (attacked == "독") ret = 2;
	}
	else if (attack == "독")
	{
		if (attacked == "독" || attacked == "고스트" || attacked == "바위" || attacked == "땅") ret = 0.5;
		else if (attacked == "풀") ret = 2;
	}
	else if (attack == "고스트")
	{
		if (attacked == "에스퍼" || attacked == "고스트") ret = 2;
		else if (attacked == "노말") ret = 0;
	}

	else if (attack == "노말")
	{
		if (attacked == "바위") ret = 0.5;
		else if (attacked == "고스트") ret = 0;
	}

	else if (attack == "바위")
	{
		if (attacked == "땅") ret = 0.5;
		else if (attacked == "불" || attacked == "비행" || attacked == "벌레") ret = 2;
	}

	else if (attack == "땅")
	{
		if (attacked == "풀" || attacked == "벌레") ret = 0.5;
		else if (attacked == "전기" || attacked == "불" || attacked == "독" || attacked == "바위") ret = 2;
		else if (attacked == "비행") ret = 0;
	}

	return ret;
}

void choose(CTrainer& trainer) //트레이너 포켓몬 선택
{
	std::cout << "=====포켓몬 목록=====" << std::endl;
	std::cout << "1. 피카츄" << std::endl;
	std::cout << "2. 이상해꽃" << std::endl;
	std::cout << "3. 거북왕" << std::endl;
	std::cout << "4. 리자몽" << std::endl;
	std::cout << "5. 피죤투" << std::endl;
	std::cout << "6. 롱스톤" << std::endl;
	std::cout << "7. 버터플" << std::endl;
	std::cout << "8. 팬텀" << std::endl;
	std::cout << "9. 후딘" << std::endl;
	std::cout << "10. 망나뇽" << std::endl;
	std::cout << "=====================" << std::endl << std::endl;

	int num[3];
	std::string str, temp[100];
	std::cout << "원하는 포켓몬을 선택해 주세요.(원하는 포켓몬 이름 앞의 숫자를 입력해주세요)" << std::endl; //첫번째 포켓몬 선택
	std::cin.ignore(); //버퍼비우기
	while (1)
	{
		bool getoutofwhile = false; //무한반복 탈출 플래그
		std::getline(std::cin, str);

		int j = 0; //temp 문자열 최대 개수
		for (int i = 0; i < 100; i++) temp[i] = ""; //문자열 배열 초기화
		for (int i = 0; i < str.size(); i++) //띄어쓰기 기준으로 입력받은 값 구분
		{
			if (str[i] == ' ') j++;
			else temp[j] += str[i];
		}

		bool point = false; //서로 다른 에러메시지가 동시에 출력되는 경우 방지용 플래그
		for (int i = 0; i <= j; i++) //각 부분의 숫자가 1이상 10 이하인지 체크
		{
			//잘못된 입력 : 세자리수 이상, 1로 시작하지 않는 두자리수, 10이 아닌 두자리수, 1이상 9이하가 아닌 한자리수
			if (temp[i].size() >= 3 || (temp[i].size() == 2 && !(temp[i][0] == '1' && temp[i][1] == '0')) || (temp[i].size() == 1 && !('1' <= temp[i][0] && temp[i][0] <= '9')))
			{
				std::cout << "입력하신 숫자들 중 1에서 10 사이의 숫자가 아닌 입력이 존재합니다. 3개의 숫자를 다시 입력해주세요." << std::endl;
				point = true;
				break;
			}
		}

		if (!point) //각 부분의 숫자가 1이상 10이하인 경우
		{
			if (j > 2) std::cout << "포켓몬을 3마리보다 많게 선택할 수 없습니다. 3개의 숫자를 다시 입력해주세요." << std::endl;
			else if (j < 2) std::cout << "포켓몬을 3마리보다 적게 선택할 수 없습니다. 3개의 숫자를 다시 입력해주세요." << std::endl;
			else //3마리 선택
			{
				if (temp[0] != temp[1] && temp[0] != temp[2] && temp[1] != temp[2]) //모든 수가 다른 경우(중복x)
				{
					for (int k = 0; k < 3; k++)
					{
						if (temp[k].size() == 1) num[k] = (int)(temp[k][0] - '0'); //한자리수인 경우 저장
						else num[k] = 10; //지금까지 남은 두자리 수는 10 뿐
					}
					getoutofwhile = true;
				}
				else std::cout << "중복 선택은 불가능합니다. 3개의 숫자를 다시 입력해주세요." << std::endl; //중복된 숫자가 존재하는 경우
			}
		}

		if (getoutofwhile) break;
	}

	trainer.set_pokemons(num[0], num[1], num[2]); //트레이너 포켓몬으로 세팅

	std::cout << "메뉴로 돌아갑니다..." << std::endl;
	Sleep(1000);
	system("cls");
}

void choose_rival(CRival& rival) //라이벌 포켓몬 선택
{
	int a, b, c;
	a = rand() % 10 + 1; //첫번째 포켓몬
	while (1) //두번째 포켓몬
	{
		b = rand() % 10 + 1;
		if (a != b) break; //중복이면 다시
	}
	while (1) //세번째 포켓몬
	{
		c = rand() % 10 + 1;
		if (a != c && b != c) break; //중복이면 다시
	}

	rival.set_pokemons(a, b, c); //라이벌 포켓몬으로 세팅
}

inline void gameexit() //게임종료
{
	std::cout << "게임을 종료합니다." << std::endl;
}

