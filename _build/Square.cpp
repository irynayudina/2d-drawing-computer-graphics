#include "Square.h"
#include "Line.h"
#include <iostream>
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
void Square::translate(int x, int y) {
	x0 += x;
	x1 += x;
	x2 += x;
	x3 += x;
	y0 += y;
	y1 += y;
	y2 += y;
	y3 += y;
}
void Square::rotate(int degrees) {
	double radians = degrees * 3.14159265358979323846 / 180;
	float s = sin(radians);
	float c = cos(radians);
	int borderX = x0, borderY = y0;
	int x0t = x0 - borderX, x1t = x1 - borderX, x2t = x2 - borderX, x3t = x3 - borderX;
	int y0t = y0 - borderY, y1t = y1 - borderY, y2t = y2 - borderY, y3t = y3 - borderY;
	x0 = x0t * c - y0t * s + borderX;
	y0 = x0t * s + y0t * c + borderY;
	x1 = x1t * c - y1t * s + borderX;
	y1 = x1t * s + y1t * c + borderY;
	x2 = x2t * c - y2t * s + borderX;
	y2 = x2t * s + y2t * c + borderY;
	x3 = x3t * c - y3t * s + borderX;
	y3 = x3t * s + y3t * c + borderY;
}
void Square::draw() {
	detectBorders();
	Line l1 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l2 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l3 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	Line l4 = Line(300, 300, 400, 400, rand(), "line", color, 20);
	l1.draw(x0, y0, x1, y1);
	l2.draw(x1, y1, x2, y2);
	l3.draw(x2, y2, x3, y3);
	l4.draw(x3, y3, x0, y0);
	if (filled) {
		for (int xM = xmin; xM < xmax; xM++) {
			for (int yM = ymin; yM < ymax; yM++) {
				int intersectionsCount = 0;
				int x;
				if ((y0 >= yM && yM >= y1) || (y0 <= yM && yM <= y1)) {
					int d = 1;
					if ((y1 - y0) != 0) {
						d = (y1 - y0);
					}
					x = x0 + ((yM - y0) * (x1 - x0)) / d;
					if (x < xM) {
						intersectionsCount++;
					}
				}
				if ((y1 <= yM && yM <= y2) || (y1 >= yM && yM >= y2)) {
					int d = 1;
					if ((y2 - y1) != 0) {
						d = (y2 - y1);
					}
					x = x1 + ((yM - y1) * (x2 - x1)) / d;
					if (x < xM) {
						intersectionsCount++;
					}
				}
				if ((y2 <= yM && yM <= y3) || (y2 >= yM && yM >= y3)) {
					int d = 1;
					if ((y3 - y2) != 0) {
						d = (y3 - y2);
					}
					x = x2 + ((yM - y2) * (x3 - x2)) / d;
					if (x < xM) {
						intersectionsCount++;
					}
				}
				if ((y0 <= yM && yM <= y3) || (y0 >= yM && yM >= y3)) {
					int d = 1;
					if ((y3 - y0) != 0) {
						d = (y3 - y0);
					}
					x = x0 + ((yM - y0) * (x3 - x0)) / d;
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
void Square::detectBorders() {

	if (x0 <= x1) {
		xmin = x0;
		if (x0 >= x2) {
			xmin = x2;
			if (x2 >= x3) {
				xmin = x3;
			}
		}
		else
			if (x0 >= x3) {
				xmin = x3;
			}
	}
	else {
		xmin = x1;
		if (x1 >= x2) {
			xmin = x2;
			if (x2 >= x3) {
				xmin = x3;
			}
		}
		else
			if (x1 >= x3) {
				xmin = x3;
			}
	}
	if (y0 <= y1) {
		ymin = y0;
		if (y0 >= y2) {
			ymin = y2;
			if (y2 >= y3) {
				ymin = y3;
			}
		}
		else
			if (y0 >= y3) {
				ymin = y3;
			}
	}
	else {
		ymin = y1;
		if (y1 >= y2) {
			ymin = y2;
			if (y2 >= y3) {
				ymin = y3;
			}
		}
		else
			if (y1 >= y3) {
				ymin = y3;
			}
	}

	if (x0 >= x1) {
		xmax = x0;
		if (x0 <= x2) {
			xmax = x2;
			if (x2 <= x3) {
				xmax = x3;
			}
		}
		else
			if (x0 <= x3) {
				xmax = x3;
			}
	}
	else {
		xmax = x1;
		if (x1 <= x2) {
			xmax = x2;
			if (x2 <= x3) {
				xmax = x3;
			}
		}
		else
			if (x1 <= x3) {
				xmax = x3;
			}
	}
	if (y0 >= y1) {
		ymax = y0;
		if (y0 <= y2) {
			ymax = y2;
			if (y2 <= y3) {
				ymax = y3;
			}
		}
		else
			if (y0 <= y3) {
				ymax = y3;
			}
	}
	else {
		ymax = y1;
		if (y1 <= y2) {
			ymax = y2;
			if (y2 <= y3) {
				ymax = y3;
			}
		}
		else
			if (y1 <= y3) {
				ymax = y3;
			}
	}
	borderX = xmin;
	borderY = ymin;
	borderH = abs(ymin - ymax),
		borderW = abs(xmin - xmax);
}
void Square::detectSelectionClick() {
	int xM = GetMouseX();
	int yM = GetMouseY();
	int intersectionsCount = 0;
	int x;
	// ray method 
	// counting lines that have y = yM, check their line expressions and if x < xM - add one to intersection count
	// if intersectons count even - point is not inside, if odd - inside

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
	if ((y2 < yM && yM < y3) || (y2 > yM && yM > y3)) {
		x = x2 + ((yM - y2) * (x3 - x2)) / (y3 - y2);
		if (x < xM) {
			intersectionsCount++;
		}
	}
	if ((y0 < yM && yM < y3) || (y0 > yM && yM > y3)) {
		x = x0 + ((yM - y0) * (x3 - x0)) / (y3 - y0);
		if (x < xM) {
			intersectionsCount++;
		}
	}
	if (intersectionsCount % 2 != 0) {
		strcpy(infol, "square is selected");
		selected = true;
	}
	else {
		if (yM > screenUIHeight) {
			selected = false;
		}
		strcpy(infol, "nothing is selected");
	}
	detectBorders();
	std::cout << "1- " << x0 << " " << y0 << ";2- " << x1 << " " << y1 << ";3- " << x2 << " " << y2 << ";4- " << x3 << " " << y3 << std::endl;
	std::cout << "xmin " << xmin << "; ymin " << ymin << std::endl;
	std::cout << "xmax " << xmax << "; ymax " << ymax << std::endl;
	std::cout << "border height " << borderH << std::endl;
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
				this->borderX += mouseDelta.x;
				this->borderY += mouseDelta.y;
				this->xmin += mouseDelta.x;
				this->xmax += mouseDelta.x;
				this->ymin += mouseDelta.y;
				this->ymax += mouseDelta.y;
			}

		}
	}
}
void Square::unselect(bool s) {
	selected = !s;
}