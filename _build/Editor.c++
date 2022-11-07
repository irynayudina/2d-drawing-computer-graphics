#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string> 
#include "Globals.h"
#include "ScreenSizes.h"
#include <iostream>
#include "ColorControlButton.h"
#include "Line.h"
#include <algorithm>
#include <vector>
#include"Circle.h"
//void drawLine(int x0, int y0, int x1, int y1) {
//    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//    int err = dx + dy, e2; /* error value e_xy */
//    for (;;) {  /* loop */
//        DrawPixel(x0, y0, selectionColor);
//        if (x0 == x1 && y0 == y1) break;
//        e2 = 2 * err;
//        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */    
//        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */   
//    }
//}
void drawCircle(int xm, int ym, int r)
{
    int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
    do {
        DrawPixel(xm - x, ym + y, BLACK); /*   I. Quadrant */
        DrawPixel(xm - y, ym - x, BLACK); /*  II. Quadrant */
        DrawPixel(xm + x, ym - y, BLACK); /* III. Quadrant */
        DrawPixel(xm + y, ym + x, BLACK); /*  IV. Quadrant */
        r = err;
        if (r > x) err += ++x * 2 + 1; /* e_xy+e_x > 0 */
        if (r <= y) err += ++y * 2 + 1; /* e_xy+e_y < 0 */
    } while (x < 0);
}
void changeColor(ColorControlButton colorPressed) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float xM = GetMouseX();
        float yM = GetMouseY();
        if (CheckCollisionPointRec({ xM, yM }, *(colorPressed.rectangle))) {
            selectionColor = colorPressed.color;
            colorPressed.rectangle->width = controlsSize + 10;
            colorPressed.rectangle->height = controlsSize + 10;
            colorize = true;
        }
        else {
            colorPressed.rectangle->width = controlsSize;
            colorPressed.rectangle->height = controlsSize;
            colorize = false;
        }
    }
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    InitWindow(screenWidth, screenHeight, "2D rpimitives editor");
    SetWindowPosition(10, 40);
    // color controls buttons 
    Rectangle redR = Rectangle{ colorPalletteX, screenBorder, controlsSize, controlsSize };
    ColorControlButton *red = new ColorControlButton(&redR, RED);
    Rectangle blackR = Rectangle{ colorPalletteX + controlsSize * 2, screenBorder, controlsSize, controlsSize };
    ColorControlButton* black = new ColorControlButton(&blackR, BLACK);
    Rectangle blueR = Rectangle{ colorPalletteX + controlsSize * 4, screenBorder, controlsSize, controlsSize };
    ColorControlButton* blue = new ColorControlButton(&blueR, BLUE);
    Rectangle grayR = Rectangle{ colorPalletteX + controlsSize * 6, screenBorder, controlsSize, controlsSize };
    ColorControlButton* gray = new ColorControlButton(&grayR, GRAY);
    Rectangle greenR = Rectangle{ colorPalletteX, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    ColorControlButton* green = new ColorControlButton(&greenR, GREEN);
    Rectangle orangeR = Rectangle{ colorPalletteX + controlsSize * 2, screenBorder + controlsSize * 2, controlsSize, controlsSize};
    ColorControlButton* orange = new ColorControlButton(&orangeR, ORANGE);
    Rectangle pinkR = Rectangle{ colorPalletteX + controlsSize * 4, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    ColorControlButton* pink = new ColorControlButton(&pinkR, PINK);
    Rectangle purpleR = Rectangle{ colorPalletteX + controlsSize * 6, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    ColorControlButton* purple = new ColorControlButton(&purpleR, PURPLE);
    // figures buttons
    Rectangle line = Rectangle{ colorPalletteX, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    Rectangle triangle = Rectangle{ colorPalletteX + controlsSize * 2, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    Rectangle rectangle = Rectangle{ colorPalletteX + controlsSize * 4, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    Rectangle circle = Rectangle{ colorPalletteX + controlsSize * 6, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    // pointer decoration 
    Vector2 ballPosition = { -100.0f, -100.0f };
    Color ballColor = DARKBLUE;
    // custom lines
    std::vector<Line> lines;
    Line* classline = new Line(500, 500, 700, 800, 1, "redline", RED, 20);
    lines.push_back(*classline);
    lines.push_back(Line(600, 600, 800, 900, 2, "blueline", BLUE, 20));
    lines.push_back(Line(100, 100, 300, 300, 3, "greenline", GREEN, 20));
    // custom circles
    std::vector<Circle> circles;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        ballPosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballColor = MAROON;
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) ballColor = DARKBLUE;
        changeColor(*red);
        if (!colorize) {
            changeColor(*black);
        }if (!colorize) {
            changeColor(*blue);
        }if (!colorize) {
            changeColor(*gray);
        }if (!colorize) {
            changeColor(*green);
        }if (!colorize) {
            changeColor(*orange);
        }if (!colorize) {
            changeColor(*pink);
        }if (!colorize) {
            changeColor(*purple);
        }
        // drawFigures
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            float xM = GetMouseX();
            float yM = GetMouseY();
            if (CheckCollisionPointRec({ xM, yM }, line)) {
                lines.push_back(Line(300, 300, 400, 400, rand(), "line", RED, 20));
            }
            if (CheckCollisionPointRec({ xM, yM }, circle)) {
                circles.push_back(Circle(400, 400, 30, rand(), "circle"));
            }
        }
        std::string t;
        t = "";
        int selectedCount = 0;
        int deltasOfLinesToMouse[200];//because 100 lines
        int min = 20000;
        int minIndex = 0;
        Line* clothestline;
        figuresSelected = false;
        strcpy(info, "nothing is selected");
        for (int i = 0; i < circles.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //  || IsMouseButtonDown(MOUSE_LEFT_BUTTON)
                circles.at(i).detectSelectionClick();
            }
            if (circles.at(i).selected && colorize) {
                circles.at(i).color = selectionColor;
            }
            circles.at(i).run();
            if (circles.at(i).selected) {
                ++selectedCount;
                figuresSelected = true;
                if (selectedCount == 1) {
                    t = "xm: " + std::to_string(circles.at(i).xm) + ", ym: " + std::to_string(circles.at(i).ym);
                    strcpy(info, lines.at(i).infol);
                }
            }
        }
        for (int i = 0; i < lines.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //  || IsMouseButtonDown(MOUSE_LEFT_BUTTON)
                lines.at(i).detectSelectionClickLine(lines.at(i).x0, lines.at(i).y0, lines.at(i).x1, lines.at(i).y1, lines.at(i).boundaryPixelsOuter);
               // clothest line
                /*
                int x;
                int y;
                (x0 y0) (x1 y1) // end and start of line
                (x - x0) / (x1 - x0) = (y - y0) / (y1 - y0)
                (x - x0) * (y1 - y0) = (y - y0) * (x1 - x0)
                x * (y1 - y0) - x0 * (y1 - y0)  = y * (x1 - x0) - y0 * (x1 - x0)
                // equation of line
                x * (y1 - y0) - y * (x1 - x0) - x0 * (y1 - y0) + y0 * (x1 - x0) = 0
                // distance to line from mouse
                int xM = GetMouseX();
                int yM = GetMouseY();
                A = (y1 - y0)  B = (x1 - x0)*(-1)
                deltasOfLinesToMouse[i] = abs(xM * (y1 - y0) - yM * (x1 - x0) - x0 * (y1 - y0) + y0 * (x1 - x0))/sqrt(powA,2)+pow(B,2))
                */
            }
            if (lines.at(i).selected) {
                ++selectedCount;
                figuresSelected = true;
                if (selectedCount == 1) {
                    t = "x0: " + std::to_string(lines.at(i).x0) + ", y0: " + std::to_string(lines.at(i).y0)
                        + "\nx1: " +
                        std::to_string(lines.at(i).x1) + ", y1: " + std::to_string(lines.at(i).y1) + "\n\n";
                    strcpy(info, lines.at(i).infol);
                }
            }
            lines.at(i).run();
            if (lines.at(i).selected && colorize) {
                lines.at(i).color = selectionColor;
            }
        }
        for (int i = 0; i < lines.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                //A = (y1 - y0)  B = (x1 - x0)*(-1)
                int x0 = lines.at(i).x0;
                int y0 = lines.at(i).y0;
                int x1 = lines.at(i).x1;
                int y1 = lines.at(i).y1;
                int xM = GetMouseX();
                int yM = GetMouseY();
                deltasOfLinesToMouse[i] = abs(xM * (y1 - y0) - yM * (x1 - x0) - x0 * (y1 - y0) + y0 * (x1 - x0))
                    / sqrt(pow(y1 - y0,2) + pow((x1 - x0) * (-1),2));
            }
        }
        for (int i = 0; i < lines.size(); i++) {
            if (deltasOfLinesToMouse[i] < min) {
                min = deltasOfLinesToMouse[i];
                minIndex = i;
            }
        }
        if(figuresSelected) t = t + std::to_string(deltasOfLinesToMouse[minIndex]) + " " + lines.at(minIndex).name;
        char const* displayCoordinates = t.c_str();
        for (int i = 0; i < lines.size(); i++) {
            if (i == minIndex) {
                continue;
            }
            lines.at(i).unselect(true);
        }
                // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        // UI elements - library functions
        ClearBackground(RAYWHITE);
        DrawText("draw item from menue to canvas with a click of a mouse, \nmove and resize it with pressed mouse, \ncolor it by selecting it with a click of a mouse and clicking on color from menue, \nset rotation and scale to selected item(s) from menue, \nto select multiple hold Shift and click with a mouse on each element", screenBorder, screenBorder, controlsSize, DARKGRAY);
        DrawText(displayCoordinates, 850, screenBorder, controlsSize, RED);
        DrawText(info, 850, screenBorder + controlsSize*3, controlsSize, RED);
        // colors
        DrawRectangleRec(*red->rectangle, RED);
        DrawRectangleRec(*black->rectangle, BLACK);
        DrawRectangleRec(*blue->rectangle, BLUE);
        DrawRectangleRec(*gray->rectangle, GRAY);
        DrawRectangleRec(*green->rectangle, GREEN);
        DrawRectangleRec(*orange->rectangle, ORANGE);
        DrawRectangleRec(*pink->rectangle, PINK);
        DrawRectangleRec(*purple->rectangle, PURPLE);
        // figures
        DrawRectangleLines(line.x, line.y, line.width, line.height, BLANK);
        DrawLine(line.x, line.y, line.x + line.width, line.y+line.height, BLACK);
        DrawRectangleLines(triangle.x, triangle.y, triangle.width, triangle.height, BLANK);
        DrawTriangleLines({ triangle.x, triangle.y + triangle.height }, { triangle.x + triangle.width/2, triangle.y },
            { triangle.x + triangle.width, triangle.y + triangle.height }, BLACK);
        DrawRectangleLines(rectangle.x, rectangle.y, rectangle.width, rectangle.height, BLACK);
        DrawRectangleLines(circle.x, circle.y, circle.width, circle.height, BLANK);
        DrawCircleLines(circle.x + circle.width / 2, circle.y + circle.width / 2, circle.width / 2, BLACK);
        // pointer
        DrawLine(screenBorder, screenUIHeight, (screenWidth - screenBorder), screenUIHeight, DARKGRAY);
        DrawCircleV(ballPosition, 4, ballColor);

        // custom drawings:
        // lines
        for (int i = 0; i < lines.size(); i++) {
            lines.at(i).draw(lines.at(i).x0, lines.at(i).y0, lines.at(i).x1, lines.at(i).y1);
            if (lines.at(i).selected) {
                DrawRectangleLines(lines.at(i).selectionX, lines.at(i).selectionY, lines.at(i).selectionWidth, 
                    lines.at(i).selectionHeight, GREEN);
            }
        }
        for (int i = 0; i < circles.size(); i++) {
            circles.at(i).draw(circles.at(i).xm, circles.at(i).ym, circles.at(i).r);
            if (circles.at(i).selected) {
                DrawRectangleLines(circles.at(i).xm - circles.at(i).r, circles.at(i).ym - circles.at(i).r, 
                    circles.at(i).r * 2, circles.at(i).r * 2, GREEN);
            }
        }
        //drawCircle(200, 200, 40);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context    
    return 0;
}