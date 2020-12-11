#ifndef BOARD_H_
#define BOARD_H_

#include "Square.h"
#include "Bishop.h"
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "PieceArray.h"

class Board
{
private:
	Square board[3][4];
	Player player;
	PieceArray left;
	PieceArray right;
	void InitializePieces();
	void SwitchPlayer();
	void DrawRow(std::ostream& os, int index) const;
	bool IsWithinBoard(Position pos) const;

public:
	Board();
	void Draw(std::ostream& os) const;
	void ShowTurn(std::ostream& os) const;
	bool MovePiece(Position pos, Direction dir);
	bool PlayerHasPiece() const;
	bool PlacePiece(int pieceIndex, Position pos);
	bool IsGameOver(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

#endif
