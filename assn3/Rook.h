#ifndef ROOK_H_
#define ROOK_H_

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(Player player, Position pos);
	bool CanMoveTo(Direction dir) const;
	void PrintLabel(std::ostream& os) const;
};

#endif
