#pragma once
#include "raylib.h"
#include <stdlib.h>
#include <string> 
#include "ScreenSizes.h"
class Circle {
public:
	int xm;
	int ym;
	int r;
	Color color;
	Color fillColor;
	bool filled = false;
	char infol[50] = "nothing is selected";
	int id;
	char name[50] = "circle";
	bool selected = false;
	Circle(int xm, int ym, int r, int id, char  name[]);
	~Circle();
	void detectSelectionClick();
	void draw(int xm, int ym, int r);
	void unselect(bool s);
	void scale(float v);
	void run();
	void translate(int x, int y);
	void rotate(int degrees);
};