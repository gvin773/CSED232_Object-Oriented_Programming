#ifndef BISHOP_H_
#define BISHOP_H_

#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(Player player, Position pos);
	bool CanMoveTo(Direction dir) const;
	void PrintLabel(std::ostream& os) const;
};

#endif
