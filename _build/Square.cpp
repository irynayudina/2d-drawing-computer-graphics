#include "Square.h"
#include "Line.h"
Square::Square(int x0, int x1, int x2, int x3, int y0, int y1, int y2, int y3, Color color, int id) {
	this->x0 = x0;
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y0 = y0;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->color = color;
	this->id = id;
}
Square::~Square() {
	this->x0 = 200;
	this->x1 = 250;
	this->x2 = 300;
	this->y0 = 200;
	this->y1 = 250;
	this->y2 = 200;
	this->color = RED;
	this->id = rand();
}
void::Square::scale(float v) {
	int borderX = x0;
	int borderY = y0;
	x0 *= v;
	x1 *= v;
	x2 *= v;
	x3 *= v;
	y0 *= v;
	y1 *= v;
	y2 *= v;
	y3 *= v;

	x0 -= borderX * (v - 1);
	y0 -= borderY * (v - 1);
	x1 -= borderX * (v - 1);
	y1 -= borderY * (v - 1);
	x2 -= borderX * (v - 1);
	y2 -= borderY * (v - 1);
	x3 -= borderX * (v - 1);
	y3 -= borderY * (v - 1);
}
void Square::draw() {
	Line l1 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l2 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l3 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l4 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	l1.draw(x0, y0, x1, y1);
	l2.draw(x1, y1, x2, y2);
	l3.draw(x2, y2, x3, y3);
	l4.draw(x3, y3, x0, y0);
	if (filled) {
		for (int x = x0; x < x2; x++) {
			for (int y = y0; y < y2; y++) {
				DrawPixel(x, y, fillColor);
			}
		}
	}
}
void Square::detectSelectionClick() {
	int xM = GetMouseX();
	int yM = GetMouseY();
	// ray method simplified
	// counting lines that have y = yM, check their line expressions and if x < xM - add one to intersection count
	// if intersectons count even - point is not inside, if odd - inside
	if ((y0 <= yM && yM <= y1) && (x0 <= xM && xM <= x3)) {
		selected = true;
		strcpy(infol, "square is selected");
	}
	else {
		if (yM > screenUIHeight) {
			selected = false;
		}
		strcpy(infol, "nothing is selected");
	}
}
void Square::run() {
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int xM = GetMouseX();
		int yM = GetMouseY();
		if (selected) {
			if (yM > screenUIHeight + screenBorder && yM < screenHeight - screenBorder && xM > screenBorder && xM < screenWidth - screenBorder) {
				Vector2 mouseDelta = GetMouseDelta();
				this->x0 += mouseDelta.x;
				this->x1 += mouseDelta.x;
				this->x2 += mouseDelta.x;
				this->x3 += mouseDelta.x;
				this->y0 += mouseDelta.y;
				this->y1 += mouseDelta.y;
				this->y2 += mouseDelta.y;
				this->y3 += mouseDelta.y;
			}

		}
	}
}
void Square::unselect(bool s) {
	selected = !s;
}