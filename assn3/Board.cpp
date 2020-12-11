#include "Board.h"

void Board::InitializePieces() //��⸻ ������ �ʱ���ġ�� ��ġ
{
	Piece* pawnL = new Pawn(Player::PLAYER_LEFT, { 1, 1 });
	Piece* pawnR = new Pawn(Player::PLAYER_RIGHT, { 1, 2 });
	Piece* kingL = new King(Player::PLAYER_LEFT, { 1, 0 });
	Piece* kingR = new King(Player::PLAYER_RIGHT, { 1, 3 });
	Piece* bishopL = new Bishop(Player::PLAYER_LEFT, { 0, 0 });
	Piece* bishopR = new Bishop(Player::PLAYER_RIGHT, { 2, 3 });
	Piece* rookL = new Rook(Player::PLAYER_LEFT, { 2, 0 });
	Piece* rookR = new Rook(Player::PLAYER_RIGHT, { 0, 3 });
	board[1][1].SetPiece(pawnL);
	board[1][2].SetPiece(pawnR);
	board[1][0].SetPiece(kingL);
	board[1][3].SetPiece(kingR);
	board[0][0].SetPiece(bishopL);
	board[2][3].SetPiece(bishopR);
	board[2][0].SetPiece(rookL);
	board[0][3].SetPiece(rookR);
}

void Board::SwitchPlayer()
{
	if (this->player == Player::PLAYER_LEFT) this->player = Player::PLAYER_RIGHT;
	else this->player = Player::PLAYER_LEFT;
}

void Board::DrawRow(std::ostream& os, int index) const
{
	os << "    ��";
	for (int i = 0; i < 4; i++)
	{
		os << " ";
		if (board[index][i].GetPiece() != NULL)
		{
			if (board[index][i].GetPiece()->CanMoveTo(Direction::UPLEFT)) os << "��";
			else os << "��";
			os << "��";
			if (board[index][i].GetPiece()->CanMoveTo(Direction::UP)) os << "��";
			else os << "��";
			os << "��";
			if (board[index][i].GetPiece()->CanMoveTo(Direction::UPRIGHT)) os << "��";
			else os << "��";
			os << "��";
		}
		else
		{
			os << "������������";
		}
	}
	os << std::endl;
	//������� ù��° �� ���

	os << "    ��";
	for (int i = 0; i < 4; i++)
	{
		os << " ";
		if (board[index][i].GetPiece() != NULL)
		{
			os << "��";
			if (board[index][i].GetPiece()->GetPlayer() == Player::PLAYER_LEFT) os << "����";
			else os << "����";
			os << "����";
		}
		else
		{
			os << "������������";
		}
	}
	os << std::endl;
	//������� �ι�° �� ���

	os << "  " << index+1 << " ��";
	for (int i = 0; i < 4; i++)
	{
		os << " ";
		if (board[index][i].GetPiece() != NULL)
		{
			if (board[index][i].GetPiece()->CanMoveTo(Direction::LEFT)) os << "��";
			else os << "��";
			if (board[index][i].GetPiece()->GetPlayer() == Player::PLAYER_LEFT) os << "��";
			else os << "��";
			os << *(board[index][i].GetPiece());
			if (board[index][i].GetPiece()->GetPlayer() == Player::PLAYER_LEFT) os << "��";
			else os << "��";
			if (board[index][i].GetPiece()->CanMoveTo(Direction::RIGHT)) os << "��";
			else os << "��";
			os << "��";
		}
		else
		{
			os << "������������";
		}
	}
	os << "  " << index+1 << std::endl;
	//������� ����° �� ���

	os << "    ��";
	for (int i = 0; i < 4; i++)
	{
		os << " ";
		if (board[index][i].GetPiece() != NULL)
		{
			os << "��";
			if (board[index][i].GetPiece()->GetPlayer() == Player::PLAYER_LEFT) os << "����";
			else os << "����";
			os << "����";
		}
		else
		{
			os << "������������";
		}
	}
	os << std::endl;
	//������� �׹�° �� ���

	os << "    ��";
	for (int i = 0; i < 4; i++)
	{
		os << " ";
		if (board[index][i].GetPiece() != NULL)
		{
			if (board[index][i].GetPiece()->CanMoveTo(Direction::DOWNLEFT)) os << "��";
			else os << "��";
			os << "��";
			if (board[index][i].GetPiece()->CanMoveTo(Direction::DOWN)) os << "��";
			else os << "��";
			os << "��";
			if (board[index][i].GetPiece()->CanMoveTo(Direction::DOWNRIGHT)) os << "��";
			else os << "��";
			os << "��";
		}
		else
		{
			os << "������������";
		}
	}
	os << std::endl;
	//������� �ټ���° �� ���
}

bool Board::IsWithinBoard(Position pos) const
{
	if (0 <= pos.x && pos.x <= 2 && 0 <= pos.y && pos.y <= 3) return true;
	else return false;
}

Board::Board() : left(8), right(8)
{
	player = Player::PLAYER_LEFT;
	InitializePieces();
}

void Board::Draw(std::ostream& os) const
{
	os << std::endl;
	os << "          A          B          C          D" << std::endl;
	os << "    ��������������������������������������������������������������������������������������������������" << std::endl;
	this->DrawRow(os, 0);
	os << "    ��������������������������������������������������������������������������������������������������" << std::endl;
	this->DrawRow(os, 1);
	os << "    ��������������������������������������������������������������������������������������������������" << std::endl;
	this->DrawRow(os, 2);
	os << "    ��������������������������������������������������������������������������������������������������" << std::endl;
	os << "          A          B          C          D" << std::endl;

	os << "[Left Player's Piece]: " << left << std::endl;
	os << "[Right Player's Piece]: " << right << std::endl;
}
void Board::ShowTurn(std::ostream& os) const
{
	if (player == Player::PLAYER_LEFT) os << "Left player's turn!";
	else os << "Right player's turn!";
	os << std::endl << std::endl;
}

bool Board::MovePiece(Position pos, Direction dir)
{
	if (!IsWithinBoard(pos)) return false;
	//�߸��� ��ǥ ó��
	if (board[pos.x][pos.y].GetPiece() == NULL || board[pos.x][pos.y].GetPiece()->GetPlayer() != this->player) return false;
	//��ǥ�� �� ���� ���� ��� ó��
	if (!board[pos.x][pos.y].GetPiece()->CanMoveTo(dir)) return false;
	//�̵� �Ұ����� ���� ������ ��� ó��
	
	if ((dir == Direction::UP && pos.x-1 < 0) || (dir == Direction::UP && board[pos.x-1][pos.y].GetPiece() != NULL && board[pos.x-1][pos.y].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::DOWN && pos.x+1 > 2) || (dir == Direction::DOWN && board[pos.x+1][pos.y].GetPiece() != NULL && board[pos.x+1][pos.y].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::LEFT && pos.y-1 < 0) || (dir == Direction::LEFT && board[pos.x][pos.y-1].GetPiece() != NULL && board[pos.x][pos.y-1].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::RIGHT && pos.y+1 > 3) || (dir == Direction::RIGHT && board[pos.x][pos.y+1].GetPiece() != NULL && board[pos.x][pos.y+1].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::UPLEFT && (!(pos.x-1>=0 && pos.y-1>=0))) || (dir == Direction::UPLEFT && board[pos.x-1][pos.y-1].GetPiece() != NULL && board[pos.x-1][pos.y-1].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::UPRIGHT && !(pos.x-1>=0 && pos.y+1<=3)) || (dir == Direction::UPRIGHT && board[pos.x-1][pos.y+1].GetPiece() != NULL && board[pos.x-1][pos.y+1].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::DOWNLEFT && !(pos.x+1<=2 && pos.y-1>=0)) || (dir == Direction::DOWNLEFT && board[pos.x+1][pos.y-1].GetPiece() != NULL && board[pos.x+1][pos.y-1].GetPiece()->GetPlayer() == this->player)) return false;
	if ((dir == Direction::DOWNRIGHT && !(pos.x+1<=2 && pos.y+1<=3)) || (dir == Direction::DOWNRIGHT && board[pos.x+1][pos.y+1].GetPiece() != NULL && board[pos.x+1][pos.y+1].GetPiece()->GetPlayer() == this->player)) return false;
	//�̵��ؾ��� ���� ���̰ų�, �̵��ؾ��� ���� �� ���� �ִ� ��� ó��
	
	if (dir == Direction::UP && (board[pos.x - 1][pos.y].GetPiece() != NULL && board[pos.x - 1][pos.y].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x-1][pos.y].GetPiece());
		else right.PushPiece(board[pos.x-1][pos.y].GetPiece());
	}
	if (dir == Direction::DOWN && (board[pos.x+1][pos.y].GetPiece() != NULL && board[pos.x+1][pos.y].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x+1][pos.y].GetPiece());
		else right.PushPiece(board[pos.x+1][pos.y].GetPiece());
	}
	if (dir == Direction::LEFT && (board[pos.x][pos.y-1].GetPiece() != NULL && board[pos.x][pos.y-1].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x][pos.y-1].GetPiece());
		else right.PushPiece(board[pos.x][pos.y-1].GetPiece());
	}
	if (dir == Direction::RIGHT && (board[pos.x][pos.y+1].GetPiece() != NULL && board[pos.x][pos.y+1].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x][pos.y+1].GetPiece());
		else right.PushPiece(board[pos.x][pos.y+1].GetPiece());
	}
	if (dir == Direction::UPLEFT && (board[pos.x-1][pos.y-1].GetPiece() != NULL && board[pos.x-1][pos.y-1].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x-1][pos.y-1].GetPiece());
		else right.PushPiece(board[pos.x-1][pos.y-1].GetPiece());
	}
	if (dir == Direction::UPRIGHT && (board[pos.x-1][pos.y+1].GetPiece() != NULL && board[pos.x-1][pos.y+1].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x-1][pos.y+1].GetPiece());
		else right.PushPiece(board[pos.x-1][pos.y+1].GetPiece());
	}
	if (dir == Direction::DOWNLEFT && (board[pos.x+1][pos.y-1].GetPiece() != NULL && board[pos.x+1][pos.y-1].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x+1][pos.y-1].GetPiece());
		else right.PushPiece(board[pos.x+1][pos.y-1].GetPiece());
	}
	if (dir == Direction::DOWNRIGHT && (board[pos.x+1][pos.y+1].GetPiece() != NULL && board[pos.x+1][pos.y+1].GetPiece()->GetPlayer() != this->player))
	{
		if (player == Player::PLAYER_LEFT) left.PushPiece(board[pos.x+1][pos.y+1].GetPiece());
		else right.PushPiece(board[pos.x+1][pos.y+1].GetPiece());
	}
	//�̵��ؾ��� ���� ��� ���� �ִ� ��� �� ���� �迭�� �߰�

	if (dir == Direction::UP)
	{
		Position pos_new = { pos.x - 1, pos.y };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new); //piece ����
		board[pos.x-1][pos.y].SetPiece(board[pos.x][pos.y].GetPiece()); //square ����
	}
	else if (dir == Direction::DOWN)
	{
		Position pos_new = { pos.x + 1, pos.y };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x+1][pos.y].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	else if (dir == Direction::LEFT)
	{
		Position pos_new = { pos.x, pos.y - 1 };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x][pos.y-1].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	else if (dir == Direction::RIGHT)
	{
		Position pos_new = { pos.x, pos.y + 1 };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x][pos.y+1].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	else if (dir == Direction::UPLEFT)
	{
		Position pos_new = { pos.x - 1, pos.y - 1 };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x-1][pos.y-1].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	else if (dir == Direction::UPRIGHT)
	{
		Position pos_new = { pos.x - 1, pos.y + 1 };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x-1][pos.y+1].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	else if (dir == Direction::DOWNLEFT)
	{
		Position pos_new = { pos.x + 1, pos.y - 1 };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x+1][pos.y-1].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	else if (dir == Direction::DOWNRIGHT)
	{
		Position pos_new = { pos.x + 1, pos.y + 1 };
		board[pos.x][pos.y].GetPiece()->SetPosition(pos_new);
		board[pos.x+1][pos.y+1].SetPiece(board[pos.x][pos.y].GetPiece());
	}
	//�̵��ؾ��Ұ��� �� �� ����

	board[pos.x][pos.y].SetPiece(NULL);
	//������ġ ������

	SwitchPlayer(); //�Ϻ���
	return true; //�̵�����
}

bool Board::PlayerHasPiece() const
{
	if (this->player == Player::PLAYER_LEFT)
	{
		if (left.GetLength() == 0) return false;
		else return true;
	}
	else
	{
		if (right.GetLength() == 0) return false;
		else return true;
	}
}

bool Board::PlacePiece(int pieceIndex, Position pos)
{
	if (!PlayerHasPiece()) return false;
	//���� ���� ���� ��� ó��
	if (this->player == Player::PLAYER_LEFT && !(0 <= pieceIndex && pieceIndex < left.GetLength())) return false;
	if (this->player == Player::PLAYER_RIGHT && !(0 <= pieceIndex && pieceIndex < right.GetLength())) return false;
	//���� �迭 ���� ����� ��� ó��
	
	if (!IsWithinBoard(pos)) return false;
	//��ǥ ���� ó��
	if (board[pos.x][pos.y].GetPiece() != NULL) return false;
	//��ġ�Ϸ��� ��ǥ�� �ٸ� ���� �̹� �����ϴ� ��� ó��

	if (this->player == Player::PLAYER_LEFT && pos.y == 3) return false;
	if (this->player == Player::PLAYER_RIGHT && pos.y == 0) return false;
	//��ǥ�� ��������� ��� ó��

	if (this->player == Player::PLAYER_LEFT)
	{
		board[pos.x][pos.y].SetPiece(left.PopPieceAt(pieceIndex));
		board[pos.x][pos.y].GetPiece()->Init(Player::PLAYER_LEFT, pos);
	}
	else
	{
		board[pos.x][pos.y].SetPiece(right.PopPieceAt(pieceIndex));
		board[pos.x][pos.y].GetPiece()->Init(Player::PLAYER_RIGHT, pos);
	}
	//���κ������� pop�ؼ� ���忡 ��ġ

	SwitchPlayer(); //�Ϻ���
	return true; //��ġ����
}

bool Board::IsGameOver(std::ostream& os) const
{
	int cnt = -2;
	static int cnt_turnL = 0, cnt_turnR = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			if (board[i][j].GetPiece() != NULL && typeid(*board[i][j].GetPiece()) == typeid(King)) cnt++; //���� �� �� ���� ī��Ʈ

	if (cnt) //���� ���� ���� �ϳ��� �����ϹǷ� ���� ����
	{
		if (player == Player::PLAYER_LEFT) //PLAYER_LEFT�� ���� ������
		{
			os << "Left player's king is taken!" << std::endl;
			os << "Right player WIN!" << std::endl;
		}
		else //PLAYER_RIGHT�� ���� ������
		{
			os << "Right player's king is taken!" << std::endl;
			os << "Left player WIN!" << std::endl;
		}
		return true;
	}

	if (cnt_turnL == 2) //PLAYER_LEFT�� ��� �������� �� �� ��Ƽ�� ����
	{
		os << "Left player's king is in the enemy's region more than one turn!" << std::endl;
		os << "Left player WIN!" << std::endl;
		return true;
	}
	if (cnt_turnR == 2) //PLAYER_RIGHT�� ��� �������� �� �� ��Ƽ�� ����
	{
		os << "Right player's king is in the enemy's region more than one turn!" << std::endl;
		os << "Right player WIN!" << std::endl;
		return true;
	}
	//log�� ����� �� cnt_turn�� �ѹ��� ī���õǴ� ��� ����

	if (player == Player::PLAYER_RIGHT && cnt_turnL == 0) //PLAYER_LEFT�� ���� ���� ���(ī��Ʈx)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][3].GetPiece() != NULL && typeid(*board[i][3].GetPiece()) == typeid(King) && board[i][3].GetPiece()->GetPlayer() != this->player) cnt_turnL = 1;
		}
	}

	else if (player == Player::PLAYER_LEFT && cnt_turnL == 1) //PLAYER_RIGHT�� ���� ���� ���(ī��Ʈ1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][3].GetPiece() != NULL && typeid(*board[i][3].GetPiece()) == typeid(King) && board[i][3].GetPiece()->GetPlayer() == this->player) cnt_turnL = 2;
		}
	}

	if (player == Player::PLAYER_LEFT && cnt_turnR == 0) //PLAYER_RIGHT�� ���� ���� ���(ī��Ʈx)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][0].GetPiece() != NULL && typeid(*board[i][0].GetPiece()) == typeid(King) && board[i][0].GetPiece()->GetPlayer() != this->player) cnt_turnR = 1;
		}
	}

	else if (player == Player::PLAYER_RIGHT && cnt_turnR == 1) //PLAYER_LEFT�� ���� ���� ���(ī��Ʈ1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][0].GetPiece() != NULL && typeid(*board[i][0].GetPiece()) == typeid(King) && board[i][0].GetPiece()->GetPlayer() == this->player) cnt_turnR = 2;
		}
	}

	if (cnt_turnL == 2) //PLAYER_LEFT�� ��� �������� �� �� ��Ƽ�� ����
	{
		os << "Left player's king is in the enemy's region more than one turn!" << std::endl;
		os << "Left player WIN!" << std::endl;
		return true;
	}
	if (cnt_turnR == 2) //PLAYER_RIGHT�� ��� �������� �� �� ��Ƽ�� ����
	{
		os << "Right player's king is in the enemy's region more than one turn!" << std::endl;
		os << "Right player WIN!" << std::endl;
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
	board.Draw(os);
	return os;
}
