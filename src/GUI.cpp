#include"GUI.h"

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

GUI:: GUI(Graph* graph){
	this->graph=graph;

	fileToLoad = (char*)"classic.xml";
	this->startPlay = false;
}


void GUI::initGUI()
{
	graph = (((Scene*) scene)->graph);
	
	map<string, Camera*>::iterator it;
	for(it=graph->cameras.begin(); it!=graph->cameras.end(); it++){
		cameras.push_back((*it).second->id);
	}

	if(startPlay){
		//clean menu interface
		varPanel->hidden=true;
		modepanel->hidden=true;
		wireFrameGroup->hidden=true;
		cammodel->hidden=true;
		camerasGroup->hidden=true;
		lightspanel->hidden=true;
		flagPanel->hidden=true;
		
		//new interface
		socketConnect();

		int* wire = &(((Scene*) scene)->wire);

		int* cam = &(((Scene*) scene)->actualCam);


		game_varPanel = addPanel("Settings:", 1);


		game_modepanel = addPanelToPanel(game_varPanel, "Mode", 1);
		game_wireFrameGroup = addRadioGroupToPanel(game_modepanel,wire);
		addRadioButtonToGroup(game_wireFrameGroup, "\tFill");
		addRadioButtonToGroup(game_wireFrameGroup, "\tWire");
		addRadioButtonToGroup(game_wireFrameGroup, "\tPoint");

		addColumnToPanel(game_varPanel);
		game_cammodel = addPanelToPanel(game_varPanel, "Camera", 1);
		game_camerasGroup = addRadioGroupToPanel(game_cammodel,cam);

		for(unsigned int i = 0; i < cameras.size();i++){
			addRadioButtonToGroup(game_camerasGroup, (char *)cameras[i].c_str());
		}
		addRadioButtonToGroup(game_camerasGroup, "Free Camera");


		addColumnToPanel(game_varPanel);
		game_lightspanel = addPanelToPanel(game_varPanel, "Lights", 1);
		for(unsigned int i = 0; i < graph->lights.size();i++)
		{
			if (graph->lights[i].enabled)
				addCheckboxToPanel(game_lightspanel, (char*)graph->lights[i].id.c_str(), NULL, i)->set_int_val(1);
			else
				addCheckboxToPanel(game_lightspanel, (char*)graph->lights[i].id.c_str(), NULL, i)->set_int_val(0);
		}
	}else{
		int* wire = &(((Scene*) scene)->wire);

		int* cam = &(((Scene*) scene)->actualCam);


		varPanel = addPanel("Settings:", 1);


		modepanel = addPanelToPanel(varPanel, "Mode", 1);
		wireFrameGroup = addRadioGroupToPanel(modepanel,wire);
		addRadioButtonToGroup(wireFrameGroup, "\tFill");
		addRadioButtonToGroup(wireFrameGroup, "\tWire");
		addRadioButtonToGroup(wireFrameGroup, "\tPoint");

		addColumnToPanel(varPanel);
		cammodel = addPanelToPanel(varPanel, "Camera", 1);
		camerasGroup = addRadioGroupToPanel(cammodel,cam);

		for(unsigned int i = 0; i < cameras.size();i++){
			addRadioButtonToGroup(camerasGroup, (char *)cameras[i].c_str());
		}
		addRadioButtonToGroup(camerasGroup, "Free Camera");


		addColumnToPanel(varPanel);
		lightspanel = addPanelToPanel(varPanel, "Lights", 1);
		for(unsigned int i = 0; i < graph->lights.size();i++)
		{
			if (graph->lights[i].enabled)
				addCheckboxToPanel(lightspanel, (char*)graph->lights[i].id.c_str(), NULL, i)->set_int_val(1);
			else
				addCheckboxToPanel(lightspanel, (char*)graph->lights[i].id.c_str(), NULL, i)->set_int_val(0);
		}

		addColumnToPanel(varPanel);
		flagPanel = addPanelToPanel(varPanel, "Flag", 1);
		windSpinner = addSpinnerToPanel(flagPanel, "Wind", GLUI_SPINNER_INT, &wind);

		windSpinner->set_int_limits(0, 10, GLUI_LIMIT_WRAP);
	}
}


void GUI::processGUI(GLUI_Control *ctrl)
{	
	if(ctrl->user_id == windSpinner->get_id())
		graph->setWind(wind);

	if (ctrl->user_id >= 0)
		if (ctrl->get_int_val() == 1) {
			graph->lights[ctrl->user_id].enabled = true;
			((Scene *) scene)->lights[ctrl->user_id]->enable();
		} else {
			graph->lights[ctrl->user_id].enabled = false;
			((Scene *) scene)->lights[ctrl->user_id]->disable();

		}
}

void GUI::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		performPicking(x,y);
}

void GUI::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void GUI::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
		printf("%d ",selected[i]);
		printf("\n");

		//selected[0] defenido em gamas
			//0 e 14 -- pe�as
		//selected[0] >= 15 e selected[1]
			//0 e 7 -- casas
			//8 e 14 -- cercas
			//15 e 21 -- cercas laterais

		//Menu
		if(graph->rootId == "menuRoot"){
			// Ambient
			if(selected[0] == -1) {
				if(selected[1] == 1)
					fileToLoad = (char*)"classic.xml";
				else if(selected[1] == 2)
					fileToLoad = (char*)"modern.xml";
				else
					fileToLoad = (char*)"garden.xml";
			}else if(selected[0] == -4){//play and exit
				if(selected[1] == 1)
					startGame();
				else{
					printf("\nExiting...\n");
					exit(-1);
				}
			}
		}else{
			if(selected[0] >= 0 && selected[0] < 14){ //peca
				((Scene*) scene)->game->processHit(selected[0]);
			}else
				((Scene*) scene)->game->processHit(selected[0], selected[1]);
		}
	}else
		printf("Nothing selected while picking \n");
}

void GUI::startGame(){
	Graph * pgraph = new Graph();
	ANFScene anf = ANFScene(fileToLoad, pgraph);

	string ambient = "";
	if(fileToLoad == "classic.xml")
		ambient = "classic";
	else if(fileToLoad == "modern.xml")
		ambient = "modern";
	else
		ambient = "garden";

	startPlay = true;

	((Scene*)scene)->graph = pgraph;
	((Scene*)scene)->game->ambient = ambient;
	((Scene*)scene)->init();

	initGUI();

}