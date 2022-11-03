 #pragma once
#include "raylib.h"
#include <stdlib.h>
#include <string> 
//#include "Globals.h"
class Line {
public:
	int id;
	Color color;
	int x0;
	int y0;
	int x1;
	int y1;
	int boundaryPixelsOuter;
	Line(int x0, int y0, int x1, int y1, Color color, int id, int boundaryPixelsOuter);
	~Line();
	void draw();
	//void run();
};