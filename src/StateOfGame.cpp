#include"StateOfGame.h"

Piece::Piece(){
	this->selected = false;
	this->move = false;
	this->anim = false;
}

Piece::Piece(string type, float coordX, float coordZ){
	this->type=type;
	this->coordX=coordX;
	this->coordZ=coordZ;
	this->selected = false;
	this->move = false;
	this->anim = false;
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
	Piece w1 = Piece("white", 4, 1); //alterado
	Piece r1 = Piece("red", 4, 7); //alterado

	//pieces outside the board
	Piece w2 = Piece("white", -1, -1);
	Piece w3 = Piece("white", -1, -1);
	Piece w4 = Piece("white", -1, -1);
	Piece w5 = Piece("white", -1, -1);
	Piece w6 = Piece("white", -1, -1);
	Piece w7 = Piece("white", -1, -1);

	//pieces outside the board
	Piece r2 = Piece("red", -1, -1);
	Piece r3 = Piece("red", -1, -1);
	Piece r4 = Piece("red", -1, -1);
	Piece r5 = Piece("red", -1, -1);
	Piece r6 = Piece("red", -1, -1);
	Piece r7 = Piece("red", -1, -1);

	//piece inside the board
	pieces.push_back(w1);

	pieces.push_back(w2);
	pieces.push_back(w3);
	pieces.push_back(w4);
	pieces.push_back(w5);
	pieces.push_back(w6);
	pieces.push_back(w7);

	//piece inside the board
	pieces.push_back(r1);

	pieces.push_back(r2);
	pieces.push_back(r3);
	pieces.push_back(r4);
	pieces.push_back(r5);
	pieces.push_back(r6);
	pieces.push_back(r7);

	for(unsigned int i=0; i < 7; i++){
		for(unsigned int j=0; j < 7; j++){ 
			placeholders.push_back(Placeholder(j, i + 15));
		}
	}

	placeholders[3].piece = &pieces[0];
	placeholders[45].piece = &pieces[7];

	/*placeholders outside the board*/
	for(unsigned int i=0; i < 6; i++){
		placeholders1.push_back(Placeholder());
		placeholders1[i].piece = &pieces[i+1];
	}

	for(unsigned int i=0; i < 6; i++){
		placeholders2.push_back(Placeholder());
		placeholders2[i].piece = &pieces[i+8];
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

			if(pieces[i].coordX == -1 && pieces[i].coordZ == -1){
				if(pieces[i].type == "white")
					glTranslatef(-1.0, 0.0, 13.5+5*((i+1)%6));
				else
					glTranslatef(50.0, 0.0, 13.5+5*((i+1)%6));
			}
			glLoadName(i);
			pieces[i].draw();
		glPopMatrix();
	}

	glPopMatrix();

}

void Piece::draw(){
	glPushMatrix();

	if(anim)
		animation->apply();

	if(coordX != -1 && coordZ != -1)
		glTranslatef(6.0*(coordX-1)+2.5, 0.25, (coordZ-1)*6.0+2.5);
	else
		glTranslatef((coordX)*6.0+2.5, 0.25, (coordZ)*6.0+2.5);

		glRotatef(-90, 1, 0, 0);
		peca.draw();
	glPopMatrix();
}

void StateOfGame::processHit(int value){
	
	for(unsigned int i=0; i<pieces.size(); i++){
		if(pieces[i].selected){
			pieces[i].selected = false;
			for(unsigned int j=0; j<placeholders.size(); j++){
				if(placeholders[j].selected){
					placeholders[j].selected = false;
					break;
				}
			}
		}
	}

	if(pieces[value].type == "white" && player == 1){
		pieces[value].selected = true;
	}else if(pieces[value].type == "red" && player == 2){
		pieces[value].selected = true;
	}

}

void StateOfGame::processHit(int sel0, int sel1){
	Placeholder p;

	if(sel0 >= 15 && sel1 >= 0 && sel1 <= 7){ //placeholder
		
		for(unsigned int j=0; j<placeholders.size(); j++){//verify if already exists a placeholder selected and unselect it
			if(placeholders[j].selected){
				placeholders[j].selected = false;
				placeholders[j].piece = NULL;
				break;
			}
		}

		for(unsigned int i=0; i<pieces.size(); i++){
			if(pieces[i].selected && ((pieces[i].type=="white" && player==1) || (pieces[i].type=="red" && player==2))){
				if(pieces[i].coordX == -1 && pieces[i].coordZ == -1){
					tryToAddPiece(i, sel0, sel1);
				}else{
					sel_ph[0] = sel0;
					sel_ph[1] = sel1;
					placeholders[(sel0-15)*7+sel1].selected = true;
				}
			}else if(pieces[i].selected && !((pieces[i].type=="white" && player==1) || (pieces[i].type=="red" && player==2))){
				pieces[i].selected = false;
			}
		}
	}else{//fence
		int pZ, pX;
		unsigned int i = 0;

		for(; i<pieces.size(); i++){
			if(pieces[i].selected == true){
				pX = pieces[i].coordX;
				pZ = pieces[i].coordZ;
			}
		}

		int fenceDir = 0;
		vector<Fence>::iterator itsf = sideFences.begin();
		vector<Fence>::iterator itf = fences.begin();

		for(unsigned int i=0; i<placeholders.size(); i++){
			if(placeholders[i].selected){
				if(sel0 == sel_ph[0]-1 && sel1 == sel_ph[1]+15){
					fenceDir = 1;//up
					fences[7*(sel0-15)+sel1-15].active = true;
				}else if(sel0 == sel_ph[0] && sel1 == sel_ph[1]+7){
					fenceDir = 4;//left
					sideFences[6*(sel0-15)+sel1-8].active = true;
				}else if(sel0 == sel_ph[0] && sel1 == sel_ph[1]+8){
					fenceDir = 2;//right
					sideFences[6*(sel0-15)+sel1-8].active = true;
				}else if(sel0 == sel_ph[0] && sel1 == sel_ph[1]+15){
					fenceDir = 3;//down
					fences[7*(sel0-15)+sel1-15].active = true;
				}
				if(fenceDir != 0){
					tryToAddFence(placeholders[i], sel0, sel1, pieces[i].coordX+15, pieces[i].coordZ, sel_ph[0], sel_ph[1], fenceDir);
				}else{
					unselectAll();
				}

				break;
			}
		}
	}
}

bool StateOfGame::addPiece(int column, int row){

	stringstream message;
	message << "[addPiece, "
			<< boardToString() << ", "
			<< player << ", "
			<< column-15 << ", "
			<< row << ", "
			<< /*Npieces*/ 7
			<< "].\n";

	envia((char*) message.str().c_str(), strlen(message.str().c_str()));
	
	char ans[128];
	recebe(ans);

	if(ans != 0)
		return true;
	else
		return false;
}

bool StateOfGame::addFence(int column, int row, int columnD, int rowD, int fenceDir){


	//verificar se placeholder e placeholder de destino nao tem peças associadas

	stringstream message;
	message << "[addFence, "
			<< column-15 << ", "
			<< row << ", "
			<< columnD-15 << ", "
			<< rowD << ", "
			<< fenceDir << ", " 
			<< boardToString() << ", "
			<< player
			<< "].\n";
	
	envia((char*) message.str().c_str(), strlen(message.str().c_str()));
	
	char ans[128];
	recebe(ans);

	if(ans != 0)
		return true;
	else
		return false;
}

string StateOfGame::boardToString(){

	stringstream ss;
	vector<Placeholder>::iterator itp = placeholders.begin();
	vector<Fence>::iterator itsf = sideFences.begin();
	vector<Fence>::iterator itf = fences.begin();
	string aux = "[x,";

	//ss << "[[x,x,x,x,x,x,x,x,x,x,x,x,x,x,x],";
	ss << "[[x,";
	for(unsigned int i = 1; i <= 13; i++){ //rows
		aux = "";
		for(unsigned int j = 1; j <=13; j++){//columns
			if((i % 2) != 0){
				if((j % 2) != 0){
					if(itp->piece != NULL){ //have piece
						if(itp->piece->type == "white"){ //white piece
							if(j == 13 && i != 13)
								aux += "1,x],[x,";
							else if(j == 13 && i == 13)
								aux += "1,x]";
							else
								aux += "1,";
						}else{ //red piece
							if(j == 13 && i != 13)
								aux += "2,x],[x,";
							else if(j == 13 && i == 13)
								aux += "2,x]";
							else
								aux += "2,";
						}
					}else{
						if(j == 13 && i != 13)
							aux += "e,x],[x,";
						else if(j == 13 && i == 13)
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
					if(j == 13 && i != 13)
						if(itf->active)
							aux += "x,x],[x,";
						else
							aux += "e,x],[x,";
					else if(j == 13 && i == 13)
						if(itf->active)
							aux += "x,x]";
						else
							aux += "e,x]";
					else
						if(itf->active)
							aux += "x,x,";
						else
							aux += "e,x,";

					itf++;
				}
			}
		}

		ss << aux;

	}

	//ss << ",[x,x,x,x,x,x,x,x,x,x,x,x,x,x,x]]";
	ss << "]";

	return ss.str();

}

void StateOfGame::nextPlayer(){
	if(player == 1)
		player = 2;
	else
		player = 1;
}

bool StateOfGame::gameOver(){

	//verificar se placeholder e placeholder de destino nao tem peças associadas

	stringstream message;
	message << "[gameOver, " << boardToString() << "].\n";
	
	envia((char*) message.str().c_str(), strlen(message.str().c_str()));
	
	char ans[128];
	recebe(ans);

	if(ans != "1.\r") {
		return true;
	}

	return false;
}

void StateOfGame::tryToAddPiece(int pIt, int column, int row){
	bool res = addPiece(column, row);
	if(res == true){
		int pZ, pX;

		pX = pieces[pIt].coordX+1; //save previous location of the piece
		pZ = pieces[pIt].coordZ+1;

		pieces[pIt].coordX=row;//update piece location 
		pieces[pIt].coordZ=column-15;

		placeholders[(column-15)*7+row].piece = &pieces[pIt];
		placeholders1[7*pZ+pX].piece=NULL;

		//setup animation

		pieces[pIt].anim = true;
		vector<vector<float>> ctrlPoints;
		vector<float> aux;

		//1st ctrl point
		if(pieces[pIt].type == "white"){
			aux.push_back(pX*6.0+1.5);
			aux.push_back(0.25);
			aux.push_back(pZ*6+16+5*((pIt+1)%6));
		}else{
			aux.push_back(pX*6+2.5+50.0);
			aux.push_back(0.25);
			aux.push_back(pZ*6+16+5*((pIt+1)%6));
		}
		ctrlPoints.push_back(aux);

		//2nd ctrl point
		aux[1] = 10;
		ctrlPoints.push_back(aux);
		
		//3rd ctrl point
		aux[0] = pieces[pIt].coordX*6+2.5;
		aux[2] = pieces[pIt].coordZ*6+2.5;
		ctrlPoints.push_back(aux);

		//4th ctrl point
		aux[1] = 0.25;
		ctrlPoints.push_back(aux);

		pieces[pIt].animation = new LinearAnimation("pieceLinear", 3, "linear", ctrlPoints); 

		//endturn
		nextPlayer();
	}else
		unselectAll();
}

void StateOfGame::tryToAddFence(Placeholder p, int sel0, int sel1, int column, int row, int columnD, int rowD, int fenceDir){

	if(addFence(column, row, columnD, rowD, fenceDir) == true){
		placeholders[(sel_ph[0]-15)*7+sel_ph[1]].piece=placeholders[(p.coordZ-15)+p.coordX].piece;
		placeholders[(p.coordZ-15)+p.coordX].piece=NULL;

		for(unsigned int i=0; i<pieces.size(); i++){
			if(pieces[i].selected){
				pieces[i].coordX = sel_ph[1];
				pieces[i].coordZ = sel_ph[0];
			}
		}

		if(fenceDir == 2 || fenceDir == 4)
			fences[(sel0-15)*6+sel1].active = true;
		else{
			sideFences[(sel0-15)*7+sel1].active = true;
		}
		
		nextPlayer();
	}else
		unselectAll();
	
}

void StateOfGame::unselectAll(){
	for(unsigned int i=0; i<placeholders.size(); i++){
		if(placeholders[i].selected)
			placeholders[i].selected = false;
	}

	for(unsigned int i=0; i<pieces.size(); i++){
		if(pieces[i].selected)
			pieces[i].selected = false;
	}
}

void StateOfGame::update(unsigned long millis){
	for(unsigned int i=0; i<pieces.size(); i++)
		pieces[i].update(millis);

	for(unsigned int i=0; i<fences.size(); i++)
		fences[i].update(millis);
}

void Piece::update(unsigned long millis){
	if(anim){
		animation->update(millis);
		if(animation->finished)
			anim = false;
	}
}