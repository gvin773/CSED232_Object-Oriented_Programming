#ifndef PAWN_H_
#define PAWN_H_

#include "Piece.h"

class Pawn : public Piece
{
private:
	bool isPromoted;

public:
	Pawn(Player player, Position pos);
	void Init(Player player, Position pos);
	void SetPosition(Position pos);
	bool CanMoveTo(Direction dir) const;
	void PrintLabel(std::ostream& os) const;
};

#endif
