#ifndef PIECEARRAY_H_
#define PIECEARRAY_H_

#include "Piece.h"

class PieceArray
{
private:
	int length;
	int maxLength;
	Piece** arr;

public:
	PieceArray(int maxLength);
	~PieceArray();
	int GetLength() const;
	Piece* GetPieceAt(int index) const;
	void PushPiece(Piece* piece);
	Piece* PopPieceAt(int index);
	friend std::ostream& operator<<(std::ostream& os, const PieceArray& pa);
};

#endif
