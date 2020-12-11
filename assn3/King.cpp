#include "King.h"

King::King(Player player, Position pos)
	: Piece(player, pos)
{}

bool King::CanMoveTo(Direction dir) const
{
	return true; //�������̵�����
}

void King::PrintLabel(std::ostream& os) const
{
	os << "��";
}
