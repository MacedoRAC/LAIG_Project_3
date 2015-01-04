#include"StateOfGame.h"


Piece::Piece(string type, int coordX, int coordZ, int id1, int id2){
	this->type=type;
	this->coordX=coordX;
	this->coordZ=coordZ;
	this->id1=id1;
	this->id2=id2;
	this->selected = false;
}

Fence::Fence(int coordX, int coordZ){
	this->active = false;
	this->coordX=coordX;
	this->coordZ=coordZ;
}

StateOfGame:: StateOfGame(){
	this->player="white";
	this->winner="";
	board = new BoardPrim();  //tabuleiro
	initGame();
}

void StateOfGame:: initGame(){
	Piece w1 = Piece("white", -18, 0, 19, 0);
	pieces.push_back(w1);
	Piece r1 = Piece("red", 18, 0, 19, 6);
	pieces.push_back(r1);

}

StateOfGame:: StateOfGame(Graph* graph, char* difficulty, char* modeOfGame){
	this->player="white";
	this->graph=graph;
	difficulty=difficulty;
	modeOfGame=modeOfGame;
	winner="";
}

void StateOfGame::prologParser(string state){

}

StateOfGame& StateOfGame:: operator=(const StateOfGame & state){
	this->pieces = state.pieces;
	this->fences = state.fences;
	this->winner = state.winner;

	return *this;
}


void StateOfGame:: draw(){
	bool selected=true;

	glPushMatrix();
	glPushName(-1);

	board->draw();

	for(unsigned int i = 0; i < pieces.size(); i++){
		glPushMatrix();
			glLoadName(i);
			pieces[i].draw();
		glPopMatrix();
	}


	glPopMatrix();

}

void Piece::draw(){
	glPushMatrix();
	glTranslatef(coordX, 0.3, coordZ);
		glRotatef(-90, 1, 0, 0);
		peca.draw();
	glPopMatrix();
}

void StateOfGame::processHit(int value){
	if(this->player == pieces[value].type)
		pieces[value].selected = true;
}

void StateOfGame::processHit(int column, int line){

}