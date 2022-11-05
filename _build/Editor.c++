/*******************************************************************************************
*
*   raylib [core] example - Mouse input
*
*   Example originally created with raylib 1.0, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string> 
#include "Globals.h"
#include <iostream>
#include "ColorControlButton.h"
#include "Line.h"
#include <algorithm>
void drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
    for (;;) {  /* loop */
        DrawPixel(x0, y0, selectionColor);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */    
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */   
    }
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
    const int screenWidth = 1900;
    const int screenHeight = 950;
    const int screenBorder = 10;
    const int colorPalletteX = 1200;
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
    Rectangle orangeR = Rectangle{ colorPalletteX + controlsSize * 2, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    ColorControlButton* orange = new ColorControlButton(&orangeR, ORANGE);
    Rectangle pinkR = Rectangle{ colorPalletteX + controlsSize * 4, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    ColorControlButton* pink = new ColorControlButton(&pinkR, PINK);
    Rectangle purpleR = Rectangle{ colorPalletteX + controlsSize * 6, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    ColorControlButton* purple = new ColorControlButton(&purpleR, PURPLE);
    // pointer decoration 
    Vector2 ballPosition = { -100.0f, -100.0f };
    Color ballColor = DARKBLUE;
    // custom lines
    Line* classline = new Line(500, 500, 700, 800, RED, 1, 20, "redline");
    Line* lines[100];
    lines[0] = classline;
    lines[1] = new Line(600, 600, 800, 900, BLUE, 2, 20, "blueline");
    lines[2] = new Line(100, 100, 300, 300, GREEN, 3, 20, "greenline");
    amountOfLines = 3;
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
        std::string t;
        t = "selected count: ";
        int selectedCount = 0;
        int deltastolineends[200];//because 100 lines
        int min = 20000;
        int minIndex = 0;
        Line* clothestline;
        for (int i = 0; i < amountOfLines; i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //  || IsMouseButtonDown(MOUSE_LEFT_BUTTON)
                lines[i]->detectSelectionClickLine(lines[i]->x0, lines[i]->y0, lines[i]->x1, lines[i]->y1, lines[i]->boundaryPixelsOuter);
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

                deltastolineends[i] = abs(xM * (y1 - y0) - yM * (x1 - x0) - x0 * (y1 - y0) + y0 * (x1 - x0))/sqrt(powA,2)+pow(B,2))
                */
            }
            if (lines[i]->selected) {
                ++selectedCount;
                if (selectedCount == 1) {
                    t = "x0: " + std::to_string(lines[i]->x0) + ", y0: " + std::to_string(lines[i]->y0)
                        + "\nx1: " +
                        std::to_string(lines[i]->x1) + ", y1: " + std::to_string(lines[i]->y1);
                    strcpy(info, lines[i]->infol);
                }
            }
            lines[i]->run();
            /*if (selectedCount <= 1) {
                lines[i]->run();
            }
            else {
                lines[i]->unselect(true);
            }*/
           /* else {
                t = t + std::to_string(selectedCount) + " " + lines[i]->name + "\n";
                strcpy(info, "multiple objects are selected");
            }*/
            if (lines[i]->selected && colorize) {
                lines[i]->color = selectionColor;
            }
        }
        for (int i = 0; i < amountOfLines; i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                //A = (y1 - y0)  B = (x1 - x0)*(-1)
                int x0 = lines[i]->x0;
                int y0 = lines[i]->y0;
                int x1 = lines[i]->x1;
                int y1 = lines[i]->y1;
                int xM = GetMouseX();
                int yM = GetMouseY();
                deltastolineends[i] = abs(xM * (y1 - y0) - yM * (x1 - x0) - x0 * (y1 - y0) + y0 * (x1 - x0))
                    / sqrt(pow(y1 - y0,2) + pow((x1 - x0) * (-1),2));
            }
        }
        for (int i = 0; i < amountOfLines; i++) { //*2
            if (deltastolineends[i] < min) {
                min = deltastolineends[i];
                minIndex = i;
            }
        }
        t = std::to_string(deltastolineends[minIndex]) + " " + lines[minIndex]->name;
        char const* displayCoordinates = t.c_str();
        for (int i = 0; i < amountOfLines; i++) { //*2
            if (i == minIndex) {
                continue;
            }
            lines[i]->unselect(true);
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
        // pointer
        DrawLine(screenBorder, screenUIHeight, (screenWidth - screenBorder), screenUIHeight, DARKGRAY);
        DrawCircleV(ballPosition, 4, ballColor);
        // custom drawings:
        for (int i = 0; i < amountOfLines; i++) {
            lines[i]->draw(lines[i]->x0, lines[i]->y0, lines[i]->x1, lines[i]->y1);
            if (lines[i]->selected) {
                DrawRectangleLines(lines[i]->selectionX, lines[i]->selectionY, lines[i]->selectionWidth, lines[i]->selectionHeight, GREEN);
            }
        }
        //DrawText("Irina loves her husband Anurag meowwww", 400, 400, 30, RED);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context    
    return 0;
}