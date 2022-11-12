#include "Triangle.h"
#include "Line.h"
#include <iostream>
Triangle::Triangle(int x0, int x1, int x2, int y0, int y1, int y2, Color color, int id) {
	this->x0 = x0;
	this->x1 = x1;
	this->x2 = x2;
	this->y0 = y0;
	this->y1 = y1;
	this->y2 = y2;
	this->color = color;
	this->id = id;
}
Triangle::~Triangle() {
	this->x0 = 200;
	this->x1 = 250;
	this->x2 = 300;
	this->y0 = 200;
	this->y1 = 250;
	this->y2 = 200; 
	this->color = RED;
	this->id = rand();
}
void::Triangle::scale(float v) {
	x0 *= v;
	x1 *= v;
	x2 *= v;
	y0 *= v;
	y1 *= v;
	y2 *= v;

	x0 -= borderX * (v-1);
	x1 -= borderX * (v - 1);
	x2 -= borderX * (v - 1);
	y0 -= borderY * (v - 1);
	y1 -= borderY * (v - 1);
	y2 -= borderY * (v - 1);
}
void Triangle::draw() {
	Line l1 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l2 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l3 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	l1.draw(x0, y0, x1, y1);
	l2.draw(x1, y1, x2, y2);
	l3.draw(x2, y2, x0, y0);
	if (filled) {
		/*for (int x = x1; x < x2; x++) {
			for (int y = y0; y > y1; y--) {
				DrawLine(x0, y0, x, y, fillColor);
			}
		}*/
		for (int xM = borderX; xM < borderX + borderW; xM++) {
			for (int yM = borderY; yM < borderY + borderH; yM++) {
				int intersectionsCount = 0;
				int x;
				if ((y0 > yM && yM > y1) || (y0 < yM && yM < y1)) {
					x = x0 + ((yM - y0) * (x1 - x0)) / (y1 - y0);
					if (x < xM) {
						intersectionsCount++;
					}
				}
				if ((y1 < yM && yM < y2) || (y1 > yM && yM > y2)) {
					x = x1 + ((yM - y1) * (x2 - x1)) / (y2 - y1);
					if (x < xM) {
						intersectionsCount++;
					}
				}
				if ((y0 < yM && yM < y2) || (y0 > yM && yM > y2)) {
					x = x0 + ((yM - y0) * (x2 - x0)) / (y2 - y0);
					if (x < xM) {
						intersectionsCount++;
					}
				}
				if (intersectionsCount % 2 != 0) {
					DrawPixel(xM, yM, fillColor);
				}
			}
		}
	}
}
void Triangle::detectSelectionClick() {
	int xM = GetMouseX();
	int yM = GetMouseY();
	int intersectionsCount = 0;
	int x;
	// ray method
	// counting lines that have y = yM, check their line expressions and if x < xM - add one to intersection count
	// if intersectons count even - point is not inside, if odd - inside
	//change 1st level conditions for differently orientated triangles
	if ((y0 > yM && yM > y1) || (y0 < yM && yM < y1)) {
		x = x0 + ((yM - y0) * (x1 - x0)) / (y1 - y0);
		if (x < xM) {
			intersectionsCount++;
		}
		std::cout << "selected count 1st line(red)" << std::endl;
		std::cout << intersectionsCount << std::endl;
	}
	if ((y1 < yM && yM < y2) || (y1 > yM && yM > y2)) {
		x = x1 + ((yM - y1) * (x2 - x1)) / (y2 - y1);
		if (x < xM) {
			intersectionsCount++;
		}
		std::cout << "selected count second line(green)" << std::endl;
		std::cout << intersectionsCount << std::endl;
	}
	if ((y0 < yM && yM < y2) || (y0 > yM && yM > y2)) {
		x = x0 + ((yM - y0) * (x2 - x0)) / (y2 - y0);
		if (x < xM) {
			intersectionsCount++;
		}
	}
	if (intersectionsCount % 2 != 0) {
		selected = true;
		strcpy(infol, "triangle is selected");
		std::cout << "selected count" << std::endl;
		std::cout << intersectionsCount << std::endl;
		int xmin, xmax, ymin, ymax;
		if (x0 < x1 && x0 < x2) {
			xmin = x0;
			x1 < x2 ? xmax = x2 : xmax = x1;
		}
		else if (x1 < x0 && x1 < x2) {
			xmin = x1;
			x0 < x2 ? xmax = x2 : xmax = x0;
		}
		else if (x2 < x0 && x2 < x1) {
			xmin = x2;
			x1 < x0 ? xmax = x0 : xmax = x1;
		}
		if (y0 < y1 && y0 < y2) {
			ymin = y0;
			y1 < y2 ? ymax = y2 : ymax = y1;
		}
		else if (y1 < y0 && y1 < y2) {
			ymin = y1;
			y0 < y2 ? ymax = y2 : ymax = y0;
		}
		else if (y2 < y0 && y2 < y1) {
			ymin = y2;
			y1 < y0 ? ymax = y0 : ymax = y1;
		}
		borderX = xmin;
		borderY = ymin;
		borderH = abs(ymin - ymax),
		borderW = abs(xmin - xmax);
	}
	else {
		if (yM > screenUIHeight) {
			selected = false;
		}
		strcpy(infol, "nothing is selected");
	}
}
void Triangle::run() {
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
				this->y0 += mouseDelta.y;
				this->y1 += mouseDelta.y;
				this->y2 += mouseDelta.y;
				this->borderX += mouseDelta.x;
				this->borderY += mouseDelta.y;
			}

		}
	}
}
void Triangle::unselect(bool s) {
	selected = !s;
}