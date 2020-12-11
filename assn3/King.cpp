#include "King.h"

King::King(Player player, Position pos)
	: Piece(player, pos)
{}

bool King::CanMoveTo(Direction dir) const
{
	return true; //모든방향이동가능
}

void King::PrintLabel(std::ostream& os) const
{
	os << "王";
}
