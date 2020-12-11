#Makefile

CC = g++

list.o : list.cpp
	g++ -c list.cpp

CPokemon.o : CPokemon.cpp
	g++ -c CPokemon.cpp

CTrainer.o : CTrainer.cpp
	g++ -c CTrainer.cpp

CRival.o : CRival.cpp
	g++ -c CRival.cpp

pokemon.o : pokemon.cpp
	g++ -c pokemon.cpp

pokemon : list.o CPokemon.o CTrainer.o CRival.o pokemon.o
	g++ list.o CPokemon.o CTrainer.o CRival.o pokemon.o -o pokemon -static-libgcc -static-libstdc++