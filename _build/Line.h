 #pragma once
#include "raylib.h"
#include <stdlib.h>
#include <string> 
#include "ScreenSizes.h"
class Line {
public:
	bool end = false;
	bool line = false;
	bool start = false;
	bool selected = false;
	int selectionX = 0;
	int selectionY = 0;
	int selectionWidth = 0;
	int selectionHeight = 0;
	char infol[50] = "nothing is selected";
	int id;//
	char name[50] = "line";
	Color color;
	int x0;
	int y0;
	int x1;
	int y1;
	int boundaryPixelsOuter;
	Line(int x0, int y0, int x1, int y1, int id, char name[], Color color, int boundaryPixelsOuter);
	~Line();
	void draw(int x0, int y0, int x1, int y1);
	void detectSelectionClickLine(int x0, int y0, int x1, int y1, int boundaryPixelsOuter);
	void unselect(bool s);
	bool onTheScreen();
	void scale(float v);
	void run();
};