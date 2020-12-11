#include "Piece.h"

Piece::Piece(Player player, Position pos)
{
	this->player = player;
	this->pos = pos;
}

void Piece::Init(Player player, Position pos)
{
	this->player = player;
	this->pos = pos;
}

Player Piece::GetPlayer() const
{
	return player;
}

void Piece::SetPlayer(Player player)
{
	this->player = player;
}

Position Piece::GetPosition() const
{
	return pos;
}

void Piece::SetPosition(Position pos)
{
	this->pos = pos;
}

std::ostream& operator<<(std::ostream& os, const Piece& p)
{
	p.PrintLabel(os);
	return os;
}
