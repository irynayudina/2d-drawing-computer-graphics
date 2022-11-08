#pragma once
#include "raylib.h"
#include <stdlib.h>
class Triangle {
public:
	int x0, x1, x2, y0, y1, y2;
	Color color;
	char infol[50] = "nothing is selected";
	int id;
	bool selected = false;
	Color fillColor;
	bool filled = false;
	int borderX, borderY, borderW, borderH;
	char name[50] = "triangle";
	Triangle(int x0, int x1, int x2, int y0, int y1, int y2, Color color, int id);
	~Triangle();
	void detectSelectionClick();
	void draw();
	void unselect(bool s);
	void run();
};