#include "Board.h"
#include <string>
#include <limits>
#include <fstream>

inline void show_command(std::ostream& os);
int get_command(std::ostream& os);

inline void show_command1(std::ostream& os);
bool get_command1(std::string& position, std::string& direction);
//이동에 대한 함수

inline void show_command2(std::ostream& os);
bool get_command2(int& index, std::string& position);
//배치에 대한 함수

int main()
{
	std::string log, file_name;
	std::ofstream outFile;
	int log_turn = 0; //log파일에 몇턴째인지 기록
	std::cout << "        *****12 Chess*****" << std::endl;
	while (1) //log저장할지 선택
	{
		std::cout << "Do you want to record battle log?" << std::endl;
		std::cout << "1. Yes" << std::endl << "2. No" << std::endl << ">> ";
		std::getline(std::cin, log);
		if (log.size() == 1 && (log[0] == '1' || log[0] == '2')) break;
		std::cout << "\n[ERROR] You should input the number 1 or 2!\n\n";
	}

	if (log[0] == '1') //기록을 희망하는 경우
	{
		std::cout << "\nIt will be saved as a .txt file in the same directory of this .exe file." << std::endl;
		std::cout << "Please enter the name of the log file." << std::endl;
		std::cout << "(If you want to create a file named Battle1.txt, enter only Battle1)" << std::endl;
		std::cout << ">> ";
		std::getline(std::cin, file_name);
		file_name = file_name + ".txt";
		outFile.open(file_name); //파일오픈
	}

	std::cout << "\nStart Game!" << std::endl;

	Board game;
	std::cout << game << std::endl;
	game.ShowTurn(std::cout);
	//보드판 보여주기
	while (1)
	{
		int command = 0;
		show_command(std::cout);
		while (!(command = get_command(std::cout))) //command에 대입 -> 0이면 재입력
		{
			std::cout << "\n[ERROR] You should input the number between 1 and 3!\n\n";
			std::cout << game << std::endl;
			show_command(std::cout);
		}
		//명령처리

		if (command == 1) //Move
		{
			std::cout << game << std::endl;
			game.ShowTurn(std::cout);
			//보드판 보여주기

			show_command1(std::cout);
			while (1)
			{
				std::string position, direction;
				while (!get_command1(position, direction))
				{
					std::cout << "\n[ERROR] Please enter the position and direction separated by spacing as shown in the example.\n\n";
					std::cout << game << std::endl;
					show_command1(std::cout);
				}
				//입력 자체가 잘못된 경우 처리

				Position pos{ position[1] - '1', position[0] - 'A' }; //좌표저장
				Direction dir = Direction::UP;
				if (direction == "up") dir = Direction::UP;
				else if (direction == "down") dir = Direction::DOWN;
				else if (direction == "left") dir = Direction::LEFT;
				else if (direction == "right") dir = Direction::RIGHT;
				else if (direction == "upleft") dir = Direction::UPLEFT;
				else if (direction == "upright") dir = Direction::UPRIGHT;
				else if (direction == "downleft") dir = Direction::DOWNLEFT;
				else dir = Direction::DOWNRIGHT;
				//방향 저장

				if (!game.MovePiece(pos, dir)) //이동실패
				{
					std::cout << "\n[ERROR] Fail to move! Please check the following." << std::endl;
					std::cout << "1. There is no piece in that position." << std::endl;
					std::cout << "2. The piece is not yours." << std::endl;
					std::cout << "3. The piece cannot move to that direction." << std::endl;
					std::cout << "4. The destination of this move is out of the board." << std::endl;
					std::cout << "5. There is already another your piece in the destination of this move." << std::endl << std::endl;
					std::cout << game << std::endl;
					show_command1(std::cout);
				}
				//잘못된 입력 처리

				else break; //이동후 턴변경까지 성공
			}
		}
		
		else if (command == 2) //Place
		{
			if (!game.PlayerHasPiece()) //플레이어가 가진 말이 없는 경우
			{
				std::cout << "\n[ERROR] There is no piece to place" << std::endl << std::endl;
				std::cout << game << std::endl;
				game.ShowTurn(std::cout);
				continue;
			}

			std::cout << game << std::endl;
			game.ShowTurn(std::cout);
			//보드판 보여주기

			show_command2(std::cout);
			while (1)
			{
				int index;
				std::string position;
				while (!get_command2(index, position))
				{
					std::cout << "\n[ERROR] Please enter the index and position separated by spacing as shown in the example.\n\n";
					std::cout << game << std::endl;
					game.ShowTurn(std::cout);
					show_command2(std::cout);
				}
				//입력 자체가 잘못된 경우 처리

				Position pos{ position[1] - '1', position[0] - 'A' }; //좌표 저장

				if (!game.PlacePiece(index, pos)) //배치실패
				{
					std::cout << "\n[ERROR] Fail to place! Please check the following." << std::endl;
					std::cout << "1. Index for piece is out of bound." << std::endl;
					std::cout << "2. You cannot place a piece in the enemy's region." << std::endl;
					std::cout << "3. There is already a piece in that position." << std::endl << std::endl;
					std::cout << game << std::endl;
					game.ShowTurn(std::cout);
					show_command2(std::cout);
				}
				//잘못된 입력 처리

				else break; //배치후 턴변경까지 성공
			}
		}
		else //command == 3 : Quit
		{
			std::cout << "END...";
			if (log[0] == '1') outFile << "The game was terminated by the player." << std::endl;
			break; //프로그램 종료
		}

		std::cout << game << std::endl; //보드판 보여주기
		if (game.IsGameOver(std::cout))
		{
			if (log[0] == '1')
			{
				log_turn++;
				outFile << "turn " << log_turn << std::endl << std::endl << game << std::endl;
				game.IsGameOver(outFile);
			}
			break; //프로그램 종료
		}
		game.ShowTurn(std::cout); //턴 출력

		if (log[0] == '1')
		{
			log_turn++;
			outFile << "turn " << log_turn << std::endl << std::endl << game << std::endl;
		}
	}

	if (log[0] == '1') outFile.close(); //파일클로즈

	return 0;
}

inline void show_command(std::ostream& os)
{
	os << "What do you want to do?" << std::endl;
	os << "1. Move piece" << std::endl;
	os << "2. Place piece" << std::endl;
	os << "3. Quit" << std::endl;
	os << ">> ";
}

int get_command(std::ostream& os)
{
	std::string command;
	std::getline(std::cin, command); //getline은 자동으로 버퍼 비워줌

	if (command.size() != 1) return 0; //한글자 입력이 아닌 경우 에러
	if ('1' <= command[0] && command[0] <= '3') return command[0] - '0'; //정상 입력인 경우 입력값 리턴
	else return 0; //1-3 사이의 값을 입력하지 않은 경우 에러
}

inline void show_command1(std::ostream& os)
{
	os << "Please enter the position of the piece and the direction to move" << std::endl;
	os << "Direction: [up, down, left, right, upleft, upright, downleft, downright]" << std::endl;
	os << "ex) A2 right" << std::endl;
	os << ">> ";
}

bool get_command1(std::string& position, std::string& direction)
{
	std::string command;
	std::getline(std::cin, command); //getline은 자동으로 버퍼 비워줌

	if (!(5<=command.size() && command.size()<=12)) return false; //좌표2글자+띄어쓰기1글자+방향(최소2글자, 최대9글자)
	if (command[2] != ' ') return false; //좌표, 방향 사이 공백 아닌 경우 처리

	std::string com_pos = command.substr(0, 2); //좌표 부분
	std::string com_dir = command.substr(3); //방향 부분

	if (!('A' <= com_pos[0] && com_pos[0] <= 'D')) return false; //좌표 첫글자가 ABCD가 아닌 경우 처리
	if (!('1' <= com_pos[1] && com_pos[1] <= '3')) return false; //좌표 두번째글자가 123이 아닌 경우 처리
	
	position = com_pos; //좌표저장
	direction = com_dir; //방향저장

	if (com_dir == "up") return true;
	if (com_dir == "down") return true;
	if (com_dir == "left") return true;
	if (com_dir == "right") return true;
	if (com_dir == "upleft") return true;
	if (com_dir == "upright") return true;
	if (com_dir == "downleft") return true;
	if (com_dir == "downright") return true;
	//올바른 방향 처리

	return false; //방향 잘못됨
}

inline void show_command2(std::ostream& os)
{
	os << "Please enter the index of the piece and the position to place" << std::endl;
	os << "ex) 3 B3" << std::endl;
	os << ">> ";
}

bool get_command2(int& index, std::string& position)
{
	std::string command;
	std::getline(std::cin, command); //getline은 자동으로 버퍼 비워줌

	if (command.size() != 4) return false; //한글자 입력이 아닌 경우 에러
	if (command[1] != ' ') return false; //인덱스, 좌표 사이 공백 아닌 경우 처리

	if (!('0' <= command[0] && command[0] <= '9')) return false; //인덱스가 숫자가 아닌 경우 처리
	index = command[0] - '1'; //인덱스 값 저장

	if (!('A' <= command[2] && command[2] <= 'D')) return false; //좌표 첫글자가 ABCD가 아닌 경우 처리
	if (!('1' <= command[3] && command[3] <= '3')) return false; //좌표 두번째글자가 123이 아닌 경우 처리
	position = command.substr(2); //좌표 저장

	return true; //입력 성공
}
