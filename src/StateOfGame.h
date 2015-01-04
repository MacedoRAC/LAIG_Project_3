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
	int coordX, coordZ; //from 1 to 7
	PiecePrim peca;
	bool selected;
	int id1, id2;

	void draw();
	Piece(){};
	Piece(string type, int coordX, int coordZ, int id1, int id2);
	~Piece(){};
};

class Fence{
public:
	int coordX, coordZ; //from 1 to 6
	bool active;

	Fence(){};
	Fence(int coordX, int coordZ);
	~Fence(){};
};

class StateOfGame{
public:
	vector<Piece> pieces;
	vector<Fence> fences;
	char* winner;
	char* difficulty;
	char* modeOfGame;
	Graph* graph;
	BoardPrim* board;
	void initGame();
	void processHit(int value);
	void processHit(int column, int line);
	string player;


	StateOfGame();
	StateOfGame(Graph* graph, char* difficulty, char* modeOfGame);
	~StateOfGame(){};
	void prologParser(string state);
	StateOfGame & operator=(const StateOfGame & state);
	void draw();
	
};

#endif