#include"StateOfGame.h"

Piece::Piece(){
	this->selected = false;
	this->move = false;
}

Piece::Piece(string type, float coordX, float coordZ){
	this->type=type;
	this->coordX=coordX;
	this->coordZ=coordZ;
	this->selected = false;
	this->move = false;
}

Fence::Fence(){
	this->active = false;
}

Fence::Fence(float coordX, float coordZ){
	this->active = false;
	this->coordX=coordX;
	this->coordZ=coordZ;
}

Placeholder::Placeholder(){
	this->selected = false;
	this->piece = NULL;
}

Placeholder::Placeholder(float coordX, float coordZ){
	this->selected = false;
	this->coordX=coordX;
	this->coordZ=coordZ;
	this->piece = NULL;
}

StateOfGame:: StateOfGame(){
	this->player = 1; // 1 -> white and 2 -> red
	this->winner = "";
	this->Pont1 = 0;
	this->Pont2 = 0;
	this->ambient = "classic";
	initGame();
}

StateOfGame:: StateOfGame(Graph* graph, char* difficulty, char* modeOfGame, string ambient){
	this->player = 1;
	this->graph=graph;
	difficulty=difficulty;
	modeOfGame=modeOfGame;
	winner="";
	this->Pont1 = 0;
	this->Pont2 = 0;
	this->ambient = ambient;
	initGame();
}

void StateOfGame:: initGame(){
	Piece w1 = Piece("white", 18, 0);
	Piece r1 = Piece("red", 18, 36);
	
	pieces.push_back(w1);
	pieces.push_back(r1);

	for(unsigned int i=0; i < 49; i++){
		placeholders.push_back(Placeholder());
	}

	for(unsigned int i=0; i < 42; i++){
		sideFences.push_back(Fence());
		fences.push_back(Fence());
	}
}

void StateOfGame::prologParser(string state){

}

StateOfGame& StateOfGame:: operator=(const StateOfGame & state){
	this->winner = state.winner;

	return *this;
}

void StateOfGame::confAppearances(){

	if(ambient == "classic"){
		//fences
		float ambF[4] = {0, 0, 0, 1};
		float difF[4] = {0, 0, 0, 1};
		float specF[4] = {0, 0, 0, 1};

		CGFappearance* appF = new CGFappearance(ambF, difF, specF, 20);

		fenceApp = new Appearance("fenceApp", "", appF, NULL);
		
		//placeholders
		float ambP[4] = {0.2, 0.2, 0.2, 1};
		float difP[4] = {0.2, 0.2, 0.2, 1};
		float specP[4] = {0.2, 0.2, 0.2, 1};

		CGFappearance* appP = new CGFappearance(ambP, difP, specP, 5);

		placeholderApp = new Appearance("placeholderApp", "", appP, NULL);
		
		//pieces
		float ambR[4] = {1, 0, 0, 1};
		float difR[4] = {1, 0, 0, 1};
		float specR[4] = {1, 0, 0, 1};

		CGFappearance* appR = new CGFappearance(ambR, difR, specR, 5);

		redPieceApp = new Appearance("redPieceApp", "", appR, NULL);

		float ambW[4] = {1, 1, 1, 1};
		float difW[4] = {1, 1, 1, 1};
		float specW[4] = {1, 1, 1, 1};

		CGFappearance* appW = new CGFappearance(ambW, difW, specW, 5);

		whitePieceApp = new Appearance("whitePieceApp", "", appW, NULL);
	}
}

void StateOfGame:: draw(){

	confAppearances();


	glPushMatrix();
	glPushName(-1);
	
	//draw placeholders
	float placeCounterX = 0;
	float placeCounterZ = 0;
	int c = 0;

	for(unsigned int i=0; i<7; i++){
		placeCounterX = 0;
		glPushMatrix();
		glLoadName(i+15);
		for(unsigned int j=0; j<7; j++){
			glPushMatrix();
				placeholderApp->app->apply();
				glPushName(j);
				placeholders[c].coordX= placeCounterX;
				placeholders[c].coordZ= placeCounterZ;
				glTranslatef(placeholders[c].coordX, 0, placeholders[c].coordZ);
				placeholders[c].draw();
				glPopName();
			glPopMatrix();

			placeCounterX += 6;
			c ++;
		}
		glPopMatrix();
		placeCounterZ += 6;
	}


	//draw side fences
	float sideFenceCounterX = 5.5;
	float sideFenceCounterZ = 2.5;
	c = 0;

	for(unsigned int i=0; i<7; i++){
		sideFenceCounterX = 5.5;
		glPushMatrix();
		glLoadName(i+15);
		for(unsigned int j=0; j<6; j++){
			glPushMatrix();
				fenceApp->app->apply();
				glPushName(j+8);
				sideFences[c].coordX = sideFenceCounterX;
				sideFences[c].coordZ = sideFenceCounterZ;
				glTranslatef(sideFences[c].coordX, 0, sideFences[c].coordZ);
				sideFences[c].draw();
				glPopName();
			glPopMatrix();

			sideFenceCounterX += 6;
			c++;
		}
		glPopMatrix();
		sideFenceCounterZ += 6;
	}


	//draw fences
	float fenceCounterX = 2.5;
	float fenceCounterZ = 5.5;
	c = 0;

	for(unsigned int i=0; i<6; i++){
		fenceCounterX = 2.5;
		glPushMatrix();
		glLoadName(i+15);
		for(unsigned int j=0; j<7; j++){
			glPushMatrix();
				fenceApp->app->apply();
				glPushName(j+15);
				fences[c].coordX = fenceCounterX;
				fences[c].coordZ = fenceCounterZ;
				glTranslatef(fences[c].coordX, 0, fences[c].coordZ);
				glRotatef(90, 0, 1, 0);
				fences[c].draw();
				glPopName();
			glPopMatrix();

			fenceCounterX += 6;
			c++;
		}
		glPopMatrix();
		fenceCounterZ += 6;
	}

	//draw pieces
	for(unsigned int i = 0; i < pieces.size(); i++){
		glPushMatrix();
			if(pieces[i].type == "white")
				whitePieceApp->app->apply();
			else
				redPieceApp->app->apply();
			glLoadName(i);
			pieces[i].draw();
		glPopMatrix();
	}

	glPopMatrix();

}

void Piece::draw(){
	glPushMatrix();
		if(selected)
			glTranslatef(coordX+2.5, 10, coordZ+2.5);
		else
			glTranslatef(coordX+2.5, 0.3, coordZ+2.5);
		glRotatef(-90, 1, 0, 0);
		peca.draw();
	glPopMatrix();
}

void StateOfGame::processHit(int value){
	
	for(unsigned int i=0; i<pieces.size(); i++){
		if(pieces[i].selected)
			return;
	}

	if(pieces[value].type == "white" && player == 1){
		pieces[value].selected = true;
	}else if(pieces[value].type == "red" && player == 2){
		pieces[value].selected = true;
	}

}

void StateOfGame::processHit(int sel0, int sel1){
	bool sendToProlog = false;
	Placeholder p;

	if(sel1 >= 0 && sel1 <= 7){ //placeholder
		for(unsigned int i=0; i<pieces.size(); i++){
			if(pieces[i].selected && ((pieces[i].type=="white" && player==1) || (pieces[i].type=="red" && player==2))){
				placeholders[(sel0-15)*7+sel1].piece = &pieces[i];
				placeholders[(sel0-15)*7+sel1].selected = true;
				sel_ph[0] = sel0;
				sel_ph[1] = sel1;
				if(!(pieces[i].coordX > 0 && pieces[i].coordX < 36 && pieces[i].coordZ > 0 && pieces[i].coordZ < 36)){
					sendToProlog = true;
					p = placeholders[(sel0-15)*7+sel1];
				}
			}
		}

		if(sendToProlog)
			addPiece(p.coordZ, p.coordX);

	}else{//fence

		string fenceDir = "";
		vector<Fence>::iterator itsf = sideFences.begin();
		vector<Fence>::iterator itf = fences.begin();

		for(unsigned int i=0; i<placeholders.size(); i++){
			if(placeholders[i].selected){
				if(sel0 == sel_ph[0]-1 && sel1 == sel_ph[1]+15){
					fenceDir = "up";
					fences[7*(sel0-15)+sel1-15].active = true;
				}else if(sel0 == sel_ph[0] && sel1 == sel_ph[1]+7){
					fenceDir = "left";
					sideFences[6*(sel0-15)+sel1-8].active = true;
				}else if(sel0 == sel_ph[0] && sel1 == sel_ph[1]+8){
					fenceDir = "right";
					sideFences[6*(sel0-15)+sel1-8].active = true;
				}else if(sel0 == sel_ph[0] && sel1 == sel_ph[1]+15){
					fenceDir = "down";
					fences[7*(sel0-15)+sel1-15].active = true;
				}
			}
		}
	}
}


bool StateOfGame::addPiece(int column, int row){

	socketConnect();

	/*if(board->selectedColumns.size() < 1 || board->selectedRows.size() < 1)
		return false;*/
	//verificar se placeholder nao tem peças associadas

	int Npieces;
	if(player == 1)
		Npieces = Npieces_white;
	else
		Npieces = Npieces_red;

	stringstream message;
	message << "[addPiece, "
			<< boardToString() << ", "
			<< player << ", "
			<< column << ", "
			<< row << ", "
			<< Npieces
			<< "]";

	envia((char*) message.str().c_str(), strlen(message.str().c_str()));
	
	char ans[128];
	recebe(ans);

/*	if(ans != "0.\r" && setBoard(ans)) {
		nextPlayer();
		/*board->clearSelected();
		log << this->getBoardString() << '\n';
		updatePontuations();
		return true;
	}*/

	return false;
}


bool StateOfGame::addFence(int column, int row, int columnD, int rowD){

	socketConnect();

	//verificar se placeholder e placeholder de destino nao tem peças associadas

	stringstream message;
	message << "[addFence, "
			<< boardToString() << ", "
			<< column << ", "
			<< row << ", "
			<< columnD << ", "
			<< rowD << ", "
			<< player
			<< "]";
	
	envia((char*) message.str().c_str(), strlen(message.str().c_str()));
	
	char ans[128];
	recebe(ans);

	/*if(ans != "0.\r" && setBoard(ans)) {
		nextPlayer();
		/*board->clearSelected();
		log << this->getBoardString() << '\n';
		updatePontuations();
		return true;
	}*/

	return false;
}


string StateOfGame::boardToString(){

	stringstream ss;
	vector<Placeholder>::iterator itp = placeholders.begin();
	vector<Fence>::iterator itsf = sideFences.begin();
	vector<Fence>::iterator itf = fences.begin();
	string aux = "[x,";

	ss << "[[x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x],";

	for(unsigned int i = 1; i <= 13; i++){
		aux = "[x,";
		for(unsigned int j = 1; j <=13; j++){
			if(i % 2 != 0){
				if(j % 2 != 0){
					if(itp->piece != NULL){ //have piece
						if(itp->piece->type == "white"){ //white piece
							if(j == 12 && i != 13)
								aux += "1,x],[x,";
							else if(j == 12 && i == 13)
								aux += "1,x]";
							else
								aux += "1,";
						}else{ //red piece
							if(j == 12 && i != 13)
								aux += "2,x],[x,";
							else if(j == 12 && i == 13)
								aux += "2,x]";
							else
								aux += "2,";
						}
					}else{
						if(j == 12 && i != 13)
							aux += "e,x],[x,";
						else if(j == 12 && i == 13)
							aux += "e,x]";
						else
							aux += "e,";
					}

					itp++;
				}else{//side fence
					if(itsf->active)
						aux += "x,";
					else
						aux += "e,";

					itsf++;
				}

			}else{//fence line
				if(j % 2 != 0){
					if(j == 12 && i != 13)
						if(itf->active)
							aux += "x,x],[x,";
						else
							aux += "e,x],[x,";
					else if(j == 12 && i == 13)
						if(itf->active)
							aux += "x,x]";
						else
							aux += "e,x]";
					else
						if(itf->active)
							aux += "x,";
						else
							aux += "e,";

					itf++;
				}
			}
		}

		ss << aux;

	}

	ss << ",[x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x]]";

	return ss.str();

}

void StateOfGame::nextPlayer(){
	if(player == 1)
		player = 2;
	else
		player = 1;
}

bool StateOfGame::gameOver(){

	socketConnect();
	//verificar se placeholder e placeholder de destino nao tem peças associadas

	stringstream message;
	message << "[gameOver, " << boardToString() << "]";
	
	envia((char*) message.str().c_str(), strlen(message.str().c_str()));
	
	char ans[128];
	recebe(ans);

	if(ans != "1.\r") {
		return true;
	}

	return false;
}