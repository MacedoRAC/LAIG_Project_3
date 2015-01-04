#pragma once
#include "Primitive.h"

class Board :public Primitive{
public:
	Board(void);
	void draw();
	void draw(Texture *t);
	~Board(void);
};