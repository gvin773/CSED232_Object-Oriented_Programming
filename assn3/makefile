#Makefile

CC = g++

Piece.o : Piece.cpp
	g++ -c Piece.cpp

Pawn.o : Pawn.cpp
	g++ -c Pawn.cpp

Bishop.o : Bishop.cpp
	g++ -c Bishop.cpp

Rook.o : Rook.cpp
	g++ -c Rook.cpp

King.o : King.cpp
	g++ -c King.cpp

Square.o : Square.cpp
	g++ -c Square.cpp

PieceArray.o : PieceArray.cpp
	g++ -c PieceArray.cpp

Board.o : Board.cpp
	g++ -c Board.cpp

main.o : main.cpp
	g++ -c main.cpp

main : Piece.o Pawn.o Bishop.o Rook.o King.o Square.o PieceArray.o Board.o main.o
	g++ Piece.o Pawn.o Bishop.o Rook.o King.o Square.o PieceArray.o Board.o main.o -o main
