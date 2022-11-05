#include "Line.h"
//#include "Globals.h"
Line::~Line() {
    this->x0 = 200;
    this->y0 = 200;
    this->x1 = 400;
    this->y1 = 400;
    this->color = BLACK;
    this->id = 2;
    this->boundaryPixelsOuter = 20;
}
Line::Line(int x0, int y0, int x1, int y1, Color color, int id, int boundaryPixelsOuter, char name[]) {
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
    std::string t = "x0: " + std::to_string(x0) + ", y0: " + std::to_string(y0)
        + "\nx1: " +
        std::to_string(x1) + ", y1: " + std::to_string(y1);
    char const* displayCoordinates = t.c_str();
    //printf(displayCoordinates);
    for (;;) {  /* loop */
        DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
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
        if (yM > 300) { //screenUIHeight
            line = false;
            selected = false;
        }
        end = false;
        start = false;
    }    
}
void Line :: run() { //int x0, int y0, int x1, int y1, int boundaryPixelsOuter, int xM, int yM, int deltaMouseX
    int xM = GetMouseX();
    int yM = GetMouseY();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        // short line check
        if ((abs(x0 - xM) >= boundaryPixelsOuter * 3) ||
            (abs(x1 - xM) >= boundaryPixelsOuter * 3) ||
            (abs(y0 - yM) >= boundaryPixelsOuter * 3) ||
            (abs(y1 - yM) >= boundaryPixelsOuter * 3)
            ) {
            // if end of line 
            if (!line && !start && end) {
                x1 = xM;
                y1 = yM;
                selectionX = x1 - boundaryPixelsOuter;
                selectionY = y1 - boundaryPixelsOuter;
                selectionWidth = abs(boundaryPixelsOuter * 2);
                selectionHeight = abs(boundaryPixelsOuter * 2);
                strcpy(infol, "end of line is selected");
            }
            // if start of line
            else if (!line && !end && start) {
                x0 = xM;
                y0 = yM;
                selectionX = x0 - boundaryPixelsOuter;
                selectionY = y0 - boundaryPixelsOuter;
                selectionWidth = abs(boundaryPixelsOuter * 2);
                selectionHeight = abs(boundaryPixelsOuter * 2);
                strcpy(infol, "start of line is selected");
            }
            // if body of line - move (transition)
            else if (!end && !start && line) {
                if (yM > 300) { // screenUIHeight
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
}