#ifndef SCENE_H
#define SCENE_H

#include"CGFscene.h"
#include"Graph.h"
#include"Primitive.h"
#include<vector>
#include"CGFapplication.h"
#include "StateOfGame.h"

class Scene: public CGFscene{
	
public:
	Graph* graph;
	vector<CGFlight *> lights;
	int  actualCam;
	int wire;
	int light0, light1, light2, light3;
	vector<Camera*>::iterator camIt;
	vector<Camera*> cameras;
	StateOfGame* game;
	string ambient;
	
	void init();
	void display();
	void update(unsigned long milis);
	void setupMenu();
	Scene(string ambient){this->ambient = ambient;};
};

#endif