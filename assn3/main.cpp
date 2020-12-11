#include "Board.h"
#include <string>
#include <limits>
#include <fstream>

inline void show_command(std::ostream& os);
int get_command(std::ostream& os);

inline void show_command1(std::ostream& os);
bool get_command1(std::string& position, std::string& direction);
//�̵��� ���� �Լ�

inline void show_command2(std::ostream& os);
bool get_command2(int& index, std::string& position);
//��ġ�� ���� �Լ�

int main()
{
	std::string log, file_name;
	std::ofstream outFile;
	int log_turn = 0; //log���Ͽ� ����°���� ���
	std::cout << "        *****12 Chess*****" << std::endl;
	while (1) //log�������� ����
	{
		std::cout << "Do you want to record battle log?" << std::endl;
		std::cout << "1. Yes" << std::endl << "2. No" << std::endl << ">> ";
		std::getline(std::cin, log);
		if (log.size() == 1 && (log[0] == '1' || log[0] == '2')) break;
		std::cout << "\n[ERROR] You should input the number 1 or 2!\n\n";
	}

	if (log[0] == '1') //����� ����ϴ� ���
	{
		std::cout << "\nIt will be saved as a .txt file in the same directory of this .exe file." << std::endl;
		std::cout << "Please enter the name of the log file." << std::endl;
		std::cout << "(If you want to create a file named Battle1.txt, enter only Battle1)" << std::endl;
		std::cout << ">> ";
		std::getline(std::cin, file_name);
		file_name = file_name + ".txt";
		outFile.open(file_name); //���Ͽ���
	}

	std::cout << "\nStart Game!" << std::endl;

	Board game;
	std::cout << game << std::endl;
	game.ShowTurn(std::cout);
	//������ �����ֱ�
	while (1)
	{
		int command = 0;
		show_command(std::cout);
		while (!(command = get_command(std::cout))) //command�� ���� -> 0�̸� ���Է�
		{
			std::cout << "\n[ERROR] You should input the number between 1 and 3!\n\n";
			std::cout << game << std::endl;
			show_command(std::cout);
		}
		//���ó��

		if (command == 1) //Move
		{
			std::cout << game << std::endl;
			game.ShowTurn(std::cout);
			//������ �����ֱ�

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
				//�Է� ��ü�� �߸��� ��� ó��

				Position pos{ position[1] - '1', position[0] - 'A' }; //��ǥ����
				Direction dir = Direction::UP;
				if (direction == "up") dir = Direction::UP;
				else if (direction == "down") dir = Direction::DOWN;
				else if (direction == "left") dir = Direction::LEFT;
				else if (direction == "right") dir = Direction::RIGHT;
				else if (direction == "upleft") dir = Direction::UPLEFT;
				else if (direction == "upright") dir = Direction::UPRIGHT;
				else if (direction == "downleft") dir = Direction::DOWNLEFT;
				else dir = Direction::DOWNRIGHT;
				//���� ����

				if (!game.MovePiece(pos, dir)) //�̵�����
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
				//�߸��� �Է� ó��

				else break; //�̵��� �Ϻ������ ����
			}
		}
		
		else if (command == 2) //Place
		{
			if (!game.PlayerHasPiece()) //�÷��̾ ���� ���� ���� ���
			{
				std::cout << "\n[ERROR] There is no piece to place" << std::endl << std::endl;
				std::cout << game << std::endl;
				game.ShowTurn(std::cout);
				continue;
			}

			std::cout << game << std::endl;
			game.ShowTurn(std::cout);
			//������ �����ֱ�

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
				//�Է� ��ü�� �߸��� ��� ó��

				Position pos{ position[1] - '1', position[0] - 'A' }; //��ǥ ����

				if (!game.PlacePiece(index, pos)) //��ġ����
				{
					std::cout << "\n[ERROR] Fail to place! Please check the following." << std::endl;
					std::cout << "1. Index for piece is out of bound." << std::endl;
					std::cout << "2. You cannot place a piece in the enemy's region." << std::endl;
					std::cout << "3. There is already a piece in that position." << std::endl << std::endl;
					std::cout << game << std::endl;
					game.ShowTurn(std::cout);
					show_command2(std::cout);
				}
				//�߸��� �Է� ó��

				else break; //��ġ�� �Ϻ������ ����
			}
		}
		else //command == 3 : Quit
		{
			std::cout << "END...";
			if (log[0] == '1') outFile << "The game was terminated by the player." << std::endl;
			break; //���α׷� ����
		}

		std::cout << game << std::endl; //������ �����ֱ�
		if (game.IsGameOver(std::cout))
		{
			if (log[0] == '1')
			{
				log_turn++;
				outFile << "turn " << log_turn << std::endl << std::endl << game << std::endl;
				game.IsGameOver(outFile);
			}
			break; //���α׷� ����
		}
		game.ShowTurn(std::cout); //�� ���

		if (log[0] == '1')
		{
			log_turn++;
			outFile << "turn " << log_turn << std::endl << std::endl << game << std::endl;
		}
	}

	if (log[0] == '1') outFile.close(); //����Ŭ����

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
	std::getline(std::cin, command); //getline�� �ڵ����� ���� �����

	if (command.size() != 1) return 0; //�ѱ��� �Է��� �ƴ� ��� ����
	if ('1' <= command[0] && command[0] <= '3') return command[0] - '0'; //���� �Է��� ��� �Է°� ����
	else return 0; //1-3 ������ ���� �Է����� ���� ��� ����
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
	std::getline(std::cin, command); //getline�� �ڵ����� ���� �����

	if (!(5<=command.size() && command.size()<=12)) return false; //��ǥ2����+����1����+����(�ּ�2����, �ִ�9����)
	if (command[2] != ' ') return false; //��ǥ, ���� ���� ���� �ƴ� ��� ó��

	std::string com_pos = command.substr(0, 2); //��ǥ �κ�
	std::string com_dir = command.substr(3); //���� �κ�

	if (!('A' <= com_pos[0] && com_pos[0] <= 'D')) return false; //��ǥ ù���ڰ� ABCD�� �ƴ� ��� ó��
	if (!('1' <= com_pos[1] && com_pos[1] <= '3')) return false; //��ǥ �ι�°���ڰ� 123�� �ƴ� ��� ó��
	
	position = com_pos; //��ǥ����
	direction = com_dir; //��������

	if (com_dir == "up") return true;
	if (com_dir == "down") return true;
	if (com_dir == "left") return true;
	if (com_dir == "right") return true;
	if (com_dir == "upleft") return true;
	if (com_dir == "upright") return true;
	if (com_dir == "downleft") return true;
	if (com_dir == "downright") return true;
	//�ùٸ� ���� ó��

	return false; //���� �߸���
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
	std::getline(std::cin, command); //getline�� �ڵ����� ���� �����

	if (command.size() != 4) return false; //�ѱ��� �Է��� �ƴ� ��� ����
	if (command[1] != ' ') return false; //�ε���, ��ǥ ���� ���� �ƴ� ��� ó��

	if (!('0' <= command[0] && command[0] <= '9')) return false; //�ε����� ���ڰ� �ƴ� ��� ó��
	index = command[0] - '1'; //�ε��� �� ����

	if (!('A' <= command[2] && command[2] <= 'D')) return false; //��ǥ ù���ڰ� ABCD�� �ƴ� ��� ó��
	if (!('1' <= command[3] && command[3] <= '3')) return false; //��ǥ �ι�°���ڰ� 123�� �ƴ� ��� ó��
	position = command.substr(2); //��ǥ ����

	return true; //�Է� ����
}
