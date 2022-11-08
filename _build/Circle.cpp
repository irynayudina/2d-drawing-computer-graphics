#include "Circle.h"
#include <iostream>
Circle::~Circle() {
	xm = 300;
	ym = 300;
	r = 30;
	strcpy(infol, "nothing is selected");
	id = std::rand();
	strcpy(name, "circle");
}
Circle::Circle(int xm, int ym, int r, int id = std::rand(), char name[] = "circle") {
	this->xm = xm;
	this->ym = ym;
	this->r = r;
	this->id = id;
	strcpy(this->name, name);
	color = BLACK;
}
void Circle::unselect(bool s) {
	selected = !s;
}
void Circle::draw(int xm, int ym, int r) {
	int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
	do {
		DrawPixel(xm - x, ym + y, color); /*   I. Quadrant */
		DrawPixel(xm - y, ym - x, color); /*  II. Quadrant */
		DrawPixel(xm + x, ym - y, color); /* III. Quadrant */
		DrawPixel(xm + y, ym + x, color); /*  IV. Quadrant */
		if (filled) {
			DrawLine(xm - x, ym + y, xm, ym, fillColor);
			DrawLine(xm - y, ym - x, xm, ym, fillColor);
			DrawLine(xm + x, ym - y, xm, ym, fillColor);
			DrawLine(xm + y, ym + x, xm, ym, fillColor);
		}
		r = err;
		if (r > x) err += ++x * 2 + 1; /* e_xy+e_x > 0 */
		if (r <= y) err += ++y * 2 + 1; /* e_xy+e_y < 0 */
	} while (x < 0);
}
void Circle::detectSelectionClick() {
	int xM = GetMouseX();
	int yM = GetMouseY();
	if (sqrt(pow(xM - xm, 2) + pow(yM - ym, 2)) < r) {
		selected = true;
		strcpy(infol, "circle is selected");
	}
	else {
		if (yM > screenUIHeight) {
			selected = false;
		}
		strcpy(infol, "nothing is selected");
	}
}
void Circle::run() {
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int xM = GetMouseX();
		int yM = GetMouseY();
		if (selected) {
			if (yM > screenUIHeight + screenBorder && yM < screenHeight - screenBorder && xM > screenBorder && xM < screenWidth - screenBorder) {
				Vector2 mouseDelta = GetMouseDelta();
				xm += mouseDelta.x;
				ym += mouseDelta.y;
			}

		}
	}
}