#include "ColorControlButton.h"
ColorControlButton::~ColorControlButton() {
	this->color = GREEN;
	this->rectangle = new Rectangle{ 0, 0, 100, 100 };
}
ColorControlButton::ColorControlButton(Rectangle* rectangle, Color color) {
	this->color = color;
	this->rectangle = rectangle;
}