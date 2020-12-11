#ifndef KING_H_
#define KING_H_

#include "Piece.h"

class King : public Piece
{
public:
	King(Player player, Position pos);
	bool CanMoveTo(Direction dir) const;
	void PrintLabel(std::ostream& os) const;
};

#endif
