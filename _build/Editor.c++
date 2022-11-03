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
void detectSelectionClickLine(int x0, int y0, int x1, int y1, int boundaryPixelsOuter) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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
            if (yM > screenUIHeight) {
                line = false;
                selected = false;
            }
            end = false;
            start = false;
        }
    }
}
void runLine(int boundaryPixelsOuter, int coordinates[]) { //int x0, int y0, int x1, int y1, int boundaryPixelsOuter, int xM, int yM, int deltaMouseX
    static int x0 = coordinates[0]; static int y0 = coordinates[1]; static int x1 = coordinates[2]; static int y1 = coordinates[3];
    int xM = GetMouseX();
    int yM = GetMouseY();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        // short line check
        if ( (abs(x0 - xM) >= boundaryPixelsOuter * 3) ||
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
                strcpy(info, "end of line is selected");
            }
            // if start of line
            else if (!line && !end && start) {
                x0 = xM;
                y0 = yM;
                selectionX = x0 - boundaryPixelsOuter;
                selectionY = y0 - boundaryPixelsOuter;
                selectionWidth = abs(boundaryPixelsOuter * 2);
                selectionHeight = abs(boundaryPixelsOuter * 2);
                strcpy(info, "start of line is selected");
            }
            // if body of line - move (transition)
            else if (!end && !start && line) {
                if (yM > screenUIHeight) {
                    Vector2 mouseDelta = GetMouseDelta();
                    x0 += mouseDelta.x;
                    x1 += mouseDelta.x;
                    y0 += mouseDelta.y;
                    y1 += mouseDelta.y;
                    selectionX = x0;
                    selectionY = y0;
                    selectionWidth = abs(x1 - x0);
                    selectionHeight = abs(y1 - y0);
                }               
                strcpy(info, "line is selected");
            }
            else {
                strcpy(info, "fall off");
            }
        }
    }
    coordinates[0] = x0;
    coordinates[1] = y0;
    coordinates[2] = x1;
    coordinates[3] = y1;
    
}
void changeColor(ColorControlButton colorPressed) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float xM = GetMouseX();
        float yM = GetMouseY();
        if (CheckCollisionPointRec({ xM, yM }, *(colorPressed.rectangle))) {
            selectionColor = colorPressed.color;
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

    const int controlsSize = 20;
    const int colorPalletteX = 1200;

    const int boundaryPixelsOuter = 20;
    int coordinates[] = { 100, 100, 250, 150 };

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


    Line* classline = new Line(500, 500, 700, 800, RED, 2, 20);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        ballPosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballColor = MAROON;
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) ballColor = DARKBLUE;

        detectSelectionClickLine(coordinates[0], coordinates[1], coordinates[2], coordinates[3], boundaryPixelsOuter);
        runLine(boundaryPixelsOuter, coordinates);

        std::string t = "x0: " + std::to_string(coordinates[0]) + ", y0: " + std::to_string(coordinates[1]) 
            + "\nx1: " +
            std::to_string(coordinates[2]) + ", y1: " + std::to_string(coordinates[3]);
        char const* displayCoordinates = t.c_str();

        changeColor(*red);
        changeColor(*black);
        changeColor(*blue);
        changeColor(*gray);
        changeColor(*green);
        changeColor(*orange);
        changeColor(*pink);
        changeColor(*purple);

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

        DrawLine(screenBorder, screenUIHeight, (screenWidth - screenBorder), screenUIHeight, DARKGRAY);
        DrawCircleV(ballPosition, 4, ballColor);
        // selection borders
        if (selected) {
            DrawRectangleLines(selectionX, selectionY, selectionWidth, selectionHeight, GRAY);
        }
        // custom drawings:
        drawLine(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
        classline->draw();

        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    
    return 0;
}