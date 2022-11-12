#pragma once
#include "raylib.h"
#include <stdlib.h>
class Square {
public:
	int x0, x1, x2, x3, y0, y1, y2, y3;
	Color color;
	char infol[50] = "nothing is selected";
	int id;
	bool selected = false;
	char name[50] = "square";
	Color fillColor;
	bool filled = false;
	Square(int x0, int x1, int x2, int x3, int y0, int y1, int y2, int y3, Color color, int id);
	~Square();
	void detectSelectionClick();
	void draw();
	void unselect(bool s);
	void run();
	void scale(float v);
	void translate(int x, int y);
	void rotate(int degrees);
};