#include"StateOfGame.h"


Piece::Piece(string type, int coordX, int coordY){
	this->type=type;
	this->coordX=coordX;
	this->coordY=coordY;
}

Fence::Fence(int coordX, int coordY){
	this->coordX=coordX;
	this->coordY=coordY;
}

StateOfGame:: StateOfGame(){
	this->winner="";
	board = new Board();  //tabuleiro
	initGame();
}

void StateOfGame:: initGame(){
	Piece w1 = Piece("white", -18, 0);
	whitePieces.push_back(w1);
	Piece r1 = Piece("red", 18, 0);
	redPieces.push_back(r1);

}

StateOfGame:: StateOfGame(Graph* graph, char* difficulty, char* modeOfGame){
	this->graph=graph;
	difficulty=difficulty;
	modeOfGame=modeOfGame;
	winner="";
}

void StateOfGame::prologParser(string state){

}

StateOfGame& StateOfGame:: operator=(const StateOfGame & state){
	this->whitePieces = state.whitePieces;
	this->redPieces = state.redPieces;
	this->fences = state.fences;
	this->winner = state.winner;

	return *this;
}


void StateOfGame:: draw(){
	bool selected=true;

	glPushMatrix();
	glPushName(-1);

	board->draw();

	for(unsigned int i = 0; i < whitePieces.size(); i++){
		whitePieces[i].draw();
	}

	for(unsigned int i = 0; i < redPieces.size(); i++){
		redPieces[i].draw();
	}

	glPopMatrix();

}