#pragma once
#include "raylib.h"
class ColorControlButton {
public:
	Rectangle*  rectangle;
	Color color;
	ColorControlButton(Rectangle*  rectangle, Color color);
	~ColorControlButton();
};