#ifndef SQUARE_H_
#define SQUARE_H_

#include "Piece.h"

class Square
{
private:
	Piece* piece;

public:
	Square();
	~Square();
	Piece* GetPiece() const;
	void SetPiece(Piece* piece);
	void Clear();
};

#endif
