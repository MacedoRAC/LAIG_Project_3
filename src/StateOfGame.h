#pragma once

#include<vector>
#include<string>
#include <sstream>
#include "Graph.h"
#include "Primitive.h"
#include "Socket.h"
#include "Appearance.h"

using namespace std;

class Piece{
public:
	string type; //red or white
	float coordX, coordZ; //from 1 to 7
	PiecePrim peca;
	bool selected, move;

	void draw();
	Piece();
	Piece(string type, float coordX, float coordZ);
	~Piece(){};
};

class Fence{
public:
	float coordX, coordZ; //from 1 to 6
	bool active;
	FencePrim fence;

	Fence();
	Fence(float coordX, float coordZ);
	void draw(){this->fence.draw();};
	~Fence(){};
};

class Placeholder{
public:
	float coordX, coordZ; //from 1 to 6
	bool selected;
	PlaceholderPrim placeholder;
	Piece* piece;

	Placeholder();
	Placeholder(float coordX, float coordZ);
	void draw(){this->placeholder.draw();};
	~Placeholder(){};
};

class StateOfGame{
public:
	char* winner;
	char* difficulty;
	char* modeOfGame;
	Graph* graph;
	int player;
	int Npieces_red;
	int Npieces_white;
	vector<Piece> pieces;
	vector<Fence> sideFences;
	vector<Fence> fences;
	vector<Placeholder> placeholders;
	int Pont1, Pont2;
	int sel_ph[2];
	string ambient;

	Appearance* fenceApp;
	Appearance* placeholderApp;
	Appearance* redPieceApp;
	Appearance* whitePieceApp;

	void initGame();
	void processHit(int value);
	void processHit(int sel0, int sel1);

	StateOfGame();
	StateOfGame(Graph* graph, char* difficulty, char* modeOfGame, string ambient);
	~StateOfGame(){};
	void prologParser(string state);
	StateOfGame & operator=(const StateOfGame & state);
	void draw();
	void confAppearances();

	//game logic methods
	bool addPiece(int column, int row);
	bool addFence(int column, int row, int columnD, int rowD);
	void nextPlayer();
	bool gameOver();
	void getPontuatiuons();
	string boardToString();
	
};
