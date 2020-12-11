#include "Square.h"

Square::Square()
{
	piece = NULL;
}

Square::~Square()
{
	if (piece != NULL) delete piece;
}

Piece* Square::GetPiece() const
{
	return piece;
}

void Square::SetPiece(Piece* piece)
{
	this->piece = piece;
}

void Square::Clear()
{
	piece = NULL;
}
