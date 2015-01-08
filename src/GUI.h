#ifndef GUI_H
#define GUI_H

#include "CGFinterface.h"
#include "Camera.h"
#include "ANFScene.h"
#include"Scene.h"

class GUI: public CGFinterface{
public:
	Graph* graph;
	Graph* gameGraph;
	vector<string>cameras;
	int wind;
	GLUI_Spinner * windSpinner;
	char* fileToLoad;
	bool startPlay;

	GLUI_Panel * varPanel;
	GLUI_Panel *modepanel;
	GLUI_RadioGroup* wireFrameGroup;
	GLUI_Panel *cammodel;
	GLUI_RadioGroup* camerasGroup;
	GLUI_Panel *lightspanel;
	GLUI_Panel *flagPanel;

	GLUI_Panel * game_varPanel;
	GLUI_Panel *game_modepanel;
	GLUI_RadioGroup* game_wireFrameGroup;
	GLUI_Panel *game_cammodel;
	GLUI_RadioGroup* game_camerasGroup;
	GLUI_Panel *game_lightspanel;

	GUI(Graph* graph);
	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);

	virtual void processMouse(int button, int state, int x, int y);	
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]);
	void startGame();

	~GUI(){};
};

#endif