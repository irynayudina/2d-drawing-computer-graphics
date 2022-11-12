#include "Line.h"
//#include "Globals.h"
Line::~Line() {
    this->x0 = 200;
    this->y0 = 200;
    this->x1 = 400;
    this->y1 = 400;
    this->color = BLACK;
    this->id = std::rand();
    this->boundaryPixelsOuter = 20;
}
Line::Line(int x0, int y0, int x1, int y1, int id, char name[], Color color = BLACK, int boundaryPixelsOuter = 20) {
    strcpy(this->name, name);
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->color = color;
    this->id = id;
    this->boundaryPixelsOuter = boundaryPixelsOuter;
}
void Line::unselect(bool s) {
    end = !s;
    start = !s;
    line = !s;
    selected = !s;
}
void Line :: draw(int x0, int y0, int x1, int y1) {

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
    for (;;) {  /* loop */
        DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}
void Line::scale(float v) {
    x0 *= v;
    x1 *= v;
    y0 *= v;
    y1 *= v;

    x0 -= selectionX * (v - 1);
    x1 -= selectionX * (v - 1);
    y0 -= selectionY * (v - 1);
    y1 -= selectionY * (v - 1);
}
void Line::translate(int x, int y) {
    x0 += x;
    x1 += x;
    y0 += y;
    y1 += y;
}
void Line::rotate(int degrees) {
    float s = sin(degrees);
    float c = cos(degrees);
    x0 = x0 * c - y0 * s;
    x1 = x1 * c - y1 * s;
    y0 = x0 * s + y0 * c;
    y1 = x1 * s + y1 * c;
}
void Line :: detectSelectionClickLine(int x0, int y0, int x1, int y1, int boundaryPixelsOuter) {
    int xM = GetMouseX();
    int yM = GetMouseY();
    // if end of line 
    if (abs(xM - x1) <= boundaryPixelsOuter && abs(yM - y1) <= boundaryPixelsOuter) {
        end = true;
        start = false;
        line = false;
        selected = true;
    }
    // if start of line
    else if (abs(xM - x0) <= boundaryPixelsOuter && abs(yM - y0) <= boundaryPixelsOuter) {
        start = true;
        end = false;
        line = false;
        selected = true;
    }
    // if body of line - move (transition)
    else if (((x0 <= xM && xM <= x1) || (x0 >= xM && xM >= x1)) && ((y0 <= yM && yM <= y1) || (y0 >= yM && yM >= y1))) {
        line = true;
        end = false;
        start = false;
        selected = true;
    }
    else {
        if (yM > screenUIHeight) { //screenUIHeight
            line = false;
            selected = false;
        }
        end = false;
        start = false;
    }    
}
bool Line::onTheScreen() {
    if (x1 > screenBorder && x0 > screenBorder &&
        x1 < screenWidth - screenBorder && x0 < screenWidth - screenBorder &&
        y0 < screenHeight && y1 < screenHeight &&
        y0 > screenUIHeight + screenBorder && y1 > screenUIHeight + screenBorder) {
        return true;
    }
    return false;
}
void Line :: run() {
    int xM = GetMouseX();
    int yM = GetMouseY();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        // if end of line 
        if (!line && !start && end) {
            if (yM > screenUIHeight + screenBorder && yM < screenHeight - screenBorder && xM > screenBorder && xM < screenWidth - screenBorder) {
                x1 = xM;
                y1 = yM;
                selectionX = x1 - boundaryPixelsOuter;
                selectionY = y1 - boundaryPixelsOuter;
                selectionWidth = abs(boundaryPixelsOuter * 2);
                selectionHeight = abs(boundaryPixelsOuter * 2);
                strcpy(infol, "end of line is selected");
            }
        }
        // if start of line
        else if (!line && !end && start) {
            if (yM > screenUIHeight + screenBorder && yM < screenHeight - screenBorder && xM > screenBorder && xM < screenWidth - screenBorder) {
                x0 = xM;
                y0 = yM;
                selectionX = x0 - boundaryPixelsOuter;
                selectionY = y0 - boundaryPixelsOuter;
                selectionWidth = abs(boundaryPixelsOuter * 2);
                selectionHeight = abs(boundaryPixelsOuter * 2);
                strcpy(infol, "start of line is selected");
            }
        }
        // if body of line - move (transition)
        else if (!end && !start && line) {
            if (yM > screenUIHeight + screenBorder && yM < screenHeight - screenBorder && xM > screenBorder && xM < screenWidth - screenBorder) { // screenUIHeight
                Vector2 mouseDelta = GetMouseDelta();
                x0 += mouseDelta.x;
                x1 += mouseDelta.x;
                y0 += mouseDelta.y;
                y1 += mouseDelta.y;
                if (x0 < x1) {
                    selectionX = x0;
                }
                else {
                    selectionX = x1;
                }
                if (y0 < y1) {
                    selectionY = y0;
                }
                else {
                    selectionY = y1;
                }
                selectionWidth = abs(x1 - x0);
                selectionHeight = abs(y1 - y0);                
            }
            strcpy(infol, "line is selected");
        }
        else {
            strcpy(infol, "fall off");
        }
        
    }
}