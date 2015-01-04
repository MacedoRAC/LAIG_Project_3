#ifndef STATEOFGAME_H
#define STATEOFGAME_H

#include<vector>
#include<string>
#include "Graph.h"
#include "Primitive.h"

using namespace std;

class Piece{
public:
	string type; //red or white
	int coordX, coordY; //from 1 to 7

	void draw();
	Piece(){};
	Piece(string type, int coordX, int coordY);
	~Piece(){};
};

class Fence{
public:
	int coordX, coordY; //from 1 to 6

	Fence(){};
	Fence(int coordX, int coordY);
	~Fence(){};
};

class StateOfGame{
public:
	vector<Piece> whitePieces, redPieces;
	vector<Fence> fences;
	char* winner;
	char* difficulty;
	char* modeOfGame;
	Graph* graph;
	Board* board;
	void initGame();


	StateOfGame();
	StateOfGame(Graph* graph, char* difficulty, char* modeOfGame);
	~StateOfGame(){};
	void prologParser(string state);
	StateOfGame & operator=(const StateOfGame & state);
	void draw();
	
};

#endif