#include "Rook.h"

Rook::Rook(Player player, Position pos)
	: Piece(player, pos)
{}

bool Rook::CanMoveTo(Direction dir) const
{
	if (dir == Direction::UP) return true;
	else if (dir == Direction::DOWN) return true;
	else if (dir == Direction::LEFT) return true;
	else if (dir == Direction::RIGHT) return true;
	else return false; //ªÛ«œ¡¬øÏ¿Ãµø∞°¥…
}

void Rook::PrintLabel(std::ostream& os) const
{
	os << "Ì‚";
}
