#include "Bishop.h"

Bishop::Bishop(Player player, Position pos)
	: Piece(player, pos)
{}

bool Bishop::CanMoveTo(Direction dir) const
{
	if (dir == Direction::UP) return false;
	else if (dir == Direction::DOWN) return false;
	else if (dir == Direction::LEFT) return false;
	else if (dir == Direction::RIGHT) return false;
	else return true; //대각선이동만 가능
}

void Bishop::PrintLabel(std::ostream& os) const
{
	os << "相";
}
