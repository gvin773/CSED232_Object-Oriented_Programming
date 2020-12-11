#include "Pawn.h"

Pawn::Pawn(Player player, Position pos)
	: Piece(player, pos)
{
	isPromoted = false;
}

void Pawn::Init(Player player, Position pos)
{
	Piece::Init(player, pos);
	isPromoted = false;
}

void Pawn::SetPosition(Position pos)
{
	Piece::SetPosition(pos);
	if (GetPlayer() == Player::PLAYER_LEFT)
	{
		if (pos.y == 3) isPromoted = true;
	}
	else
	{
		if (pos.y == 0) isPromoted = true;
	}
}

bool Pawn::CanMoveTo(Direction dir) const
{
	if (isPromoted == false) //ÀÚ
	{
		if (GetPlayer() == Player::PLAYER_LEFT && dir == Direction::RIGHT) return true;
		else if (GetPlayer() == Player::PLAYER_RIGHT && dir == Direction::LEFT) return true;
		else return false;
	}

	else //ÈÄ
	{
		if (GetPlayer() == Player::PLAYER_LEFT && (dir == Direction::UPLEFT || dir == Direction::DOWNLEFT)) return false;
		else if (GetPlayer() == Player::PLAYER_RIGHT && (dir == Direction::UPRIGHT || dir == Direction::DOWNRIGHT)) return false;
		return true;
	}
}

void Pawn::PrintLabel(std::ostream& os) const
{
	if (isPromoted == false) os << "í­";
	else os << "ý¥";
}
