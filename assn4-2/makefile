#Makefile

CC = g++

Pair.o : Pair.cpp
	g++ -c Pair.cpp

NODE.o : NODE.cpp
	g++ -c NODE.cpp

Vector.o : Vector.cpp
	g++ -c Vector.cpp

Set.o : Set.cpp
	g++ -c Set.cpp

main.o : main.cpp
	g++ -c main.cpp

main : Pair.o NODE.o Vector.o Set.o main.o
	g++ Pair.o NODE.o Vector.o Set.o main.o -o main