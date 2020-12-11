#ifndef PIECE_H_
#define PIECE_H_

#include <iostream>
#include <typeinfo>

enum class Player
{
	PLAYER_LEFT,
	PLAYER_RIGHT,
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UPLEFT,
	UPRIGHT,
	DOWNLEFT,
	DOWNRIGHT,
};

struct Position
{
	int x;
	int y;
};

class Piece
{
private:
	Player player;
	Position pos;

public:
	Piece(Player player, Position pos);
	virtual void Init(Player player, Position pos);
	Player GetPlayer() const;
	void SetPlayer(Player player);
	Position GetPosition() const;
	virtual void SetPosition(Position pos);
	virtual bool CanMoveTo(Direction dir) const = 0;
	virtual void PrintLabel(std::ostream& os) const = 0;
	friend std::ostream& operator<< (std::ostream& os, const Piece& p);
};

#endif
