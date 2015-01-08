#pragma once

#include<vector>
#include<string>
#include <sstream>
#include "Graph.h"
#include "Primitive.h"
#include "Socket.h"
#include "Appearance.h"
#include "Animation.h"

using namespace std;

class Piece{
public:
	string type; //red or white
	float coordX, coordZ; //from 1 to 7
	PiecePrim peca;
	bool selected, move, anim;
	LinearAnimation* animation;

	void draw();
	Piece();
	Piece(string type, float coordX, float coordZ);
	void update(unsigned long millis);
	~Piece(){};
};

class Fence{
public:
	float coordX, coordZ; //from 1 to 6
	bool active;
	FencePrim fence;
	bool anim;
	LinearAnimation* animation;

	Fence();
	Fence(float coordX, float coordZ);
	void draw(){this->fence.draw();};
	void update(unsigned long millis){};
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
	int player;
	int Npieces_red;
	int Npieces_white;
	vector<Piece> pieces;
	vector<Fence> sideFences;
	vector<Fence> fences;
	vector<Placeholder> placeholders;
	vector<Placeholder> placeholders1;
	vector<Placeholder> placeholders2;
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
	StateOfGame(string ambient);
	~StateOfGame(){};
	void prologParser(string state);
	StateOfGame & operator=(const StateOfGame & state);
	void draw();
	void confAppearances();
	void update(unsigned long millis);

	//game logic methods
	bool addPiece(int column, int row);
	bool addFence(int column, int row, int columnD, int rowD, int fenceDir);
	void tryToAddPiece(int pIt, int column, int row);
	void tryToAddFence(Placeholder p, int sel0, int sel1, int column, int row, int columnD, int rowD, int fenceDir);
	void nextPlayer();
	bool gameOver();
	void getPontuatiuons();
	void unselectAll();
	string boardToString();
	
};
