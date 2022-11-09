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
#include "Triangle.h"
#include "Square.h"
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
void fillWithColor(Rectangle* fillButton, Rectangle* clearButton) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float xM = GetMouseX();
        float yM = GetMouseY();
        if (CheckCollisionPointRec({ xM, yM }, *clearButton)) {
            fill = true;
            fillColor = BLANK; 
            clearButton->width = controlsSize + 10;
            clearButton->height = controlsSize + 10;
            fillButton->width = controlsSize;
            fillButton->height = controlsSize;
        }
        else if (CheckCollisionPointRec({ xM, yM }, *fillButton)) {
            fill = true;
            fillColor = selectionColor;
            fillButton->width = controlsSize + 10;
            fillButton->height = controlsSize + 10;
            clearButton->width = controlsSize;
            clearButton->height = controlsSize;
        }
        else {
            fill = false;
            fillButton->width = controlsSize;
            fillButton->height = controlsSize;
            clearButton->width = controlsSize;
            clearButton->height = controlsSize;
        } 
    }
}
int main(void)
{
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
    Rectangle fillButton = Rectangle{ colorPalletteX + controlsSize * 8, screenBorder, controlsSize, controlsSize };
    Rectangle clearButton = Rectangle{ colorPalletteX + controlsSize * 8, screenBorder + controlsSize * 2, controlsSize, controlsSize };
    
    // figures buttons
    Rectangle line = Rectangle{ colorPalletteX, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    Rectangle triangle = Rectangle{ colorPalletteX + controlsSize * 2, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    Rectangle rectangle = Rectangle{ colorPalletteX + controlsSize * 4, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    Rectangle circle = Rectangle{ colorPalletteX + controlsSize * 6, screenBorder + controlsSize * 4, controlsSize, controlsSize };
    
    // pointer decoration 
    Vector2 ballPosition = { -100.0f, -100.0f };
    Color ballColor = DARKBLUE;
    
    // custom figures
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<Triangle> triangles;
    std::vector<Square> squares;

    SetTargetFPS(60);   
    // Main game loop
    while (!WindowShouldClose())
    {
        std::string t;
        t = "";
        int selectedCount = 0;
        int deltasOfLinesToMouse[200];//because 100 lines
        int min = 20000;
        int minIndex = 0;
        Line* clothestline;
        bool circleSelected = false;
        bool lineSelected = false;
        bool triangleSelected = false;
        bool squareSelected = false;
        strcpy(info, "nothing is selected");
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
        fillWithColor(&fillButton, &clearButton);
        // drawFigures
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            float xM = GetMouseX();
            float yM = GetMouseY();
            if (CheckCollisionPointRec({ xM, yM }, line)) {
                lines.push_back(Line(300, 300, 400, 400, rand(), "line", RED, 20));
            }
            if (CheckCollisionPointRec({ xM, yM }, circle)) {
                circles.push_back(Circle(400, 400, 50, rand(), "circle"));
            }
            if (CheckCollisionPointRec({ xM, yM }, triangle)) {
                triangles.push_back(Triangle(400, 450, 500, 400, 350, 400, BLACK, rand()));
            }
            if (CheckCollisionPointRec({ xM, yM }, rectangle)) {
                squares.push_back(Square(400, 400, 500, 500, 400, 500, 500, 400, BLACK, rand()));
            }
        }
        // select and move triangles
        for (int i = 0; i < triangles.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                triangles.at(i).detectSelectionClick();
            }
            if (triangles.at(i).selected && colorize) {
                triangles.at(i).color = selectionColor;
            }
            if (triangles.at(i).selected && fill) {
                triangles.at(i).filled = true;
                triangles.at(i).fillColor = fillColor;
            }
            if (triangles.at(i).selected) {
                ++selectedCount;
                triangleSelected = true;
                if (selectedCount == 1) {
                    t = "x0: " + std::to_string(triangles.at(i).borderX) + ", y0: " + std::to_string(triangles.at(i).borderY);
                    strcpy(info, triangles.at(i).infol);
                }
                else {
                    strcpy(info, "multiple squares");
                }                
            }
            if (selectedCount <= 1) {
                if (!lineSelected && !circleSelected && !squareSelected) {
                    triangles.at(i).run();
                }
                else {
                    triangles.at(i).unselect(true);
                }
            }
            else {
                triangles.at(i).unselect(true);
            }
            if (triangles.at(i).selected && IsKeyPressed(KEY_DELETE)) {
                --selectedCount;
                triangleSelected = false;
                triangles.erase(triangles.begin() + i);
            }
        }
        //select and move squares
        for (int i = 0; i < squares.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                squares.at(i).detectSelectionClick();
            }
            if (squares.at(i).selected && colorize) {
                squares.at(i).color = selectionColor;
            }
            if (squares.at(i).selected && fill) {
                squares.at(i).filled = true;
                squares.at(i).fillColor = fillColor;
            }
            if (squares.at(i).selected) {
                ++selectedCount;
                squareSelected = true;
                if (selectedCount == 1) {
                    t = "x0: " + std::to_string(squares.at(i).x0) + ", y0: " + std::to_string(squares.at(i).y0);
                    strcpy(info, squares.at(i).infol);
                }
                else {
                    strcpy(info, "multiple squares");
                }
            }
            if (selectedCount <= 1) {
                if (!lineSelected && !circleSelected && !triangleSelected) {
                    squares.at(i).run();
                }
                else {
                    squares.at(i).unselect(true);
                }
            }
            else {
                squares.at(i).unselect(true);
            }
            if (squares.at(i).selected && IsKeyPressed(KEY_DELETE)) {
                --selectedCount;
                squareSelected = false;
                squares.erase(squares.begin() + i);
            }
        }
        // select and move circles
        for (int i = 0; i < circles.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                circles.at(i).detectSelectionClick();
            }
            if (circles.at(i).selected && colorize) {
                circles.at(i).color = selectionColor;
            }
            if (circles.at(i).selected && fill) {
                circles.at(i).filled = true;
                circles.at(i).fillColor = fillColor;
            }
            if (circles.at(i).selected) {
                ++selectedCount;
                circleSelected = true;
                if (selectedCount == 1) {
                    t = "xm: " + std::to_string(circles.at(i).xm) + ", ym: " + std::to_string(circles.at(i).ym);
                    strcpy(info, circles.at(i).infol);
                }
                else {
                    strcpy(info, "multiple circles");
                }
            }
            if (selectedCount <= 1) {
                if (!lineSelected && !triangleSelected && !squareSelected) {
                    circles.at(i).run();
                }
                else {
                    circles.at(i).unselect(true);
                }
            }
            else {
                circles.at(i).unselect(true);
            }
            if (circles.at(i).selected && IsKeyPressed(KEY_DELETE)) {
                --selectedCount;
                circleSelected = false;
                circles.erase(circles.begin() + i);
            }
        }
        // select and move lines
        for (int i = 0; i < lines.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //  || IsMouseButtonDown(MOUSE_LEFT_BUTTON)
                lines.at(i).detectSelectionClickLine(lines.at(i).x0, lines.at(i).y0, lines.at(i).x1, lines.at(i).y1, lines.at(i).boundaryPixelsOuter);
            }
            if (lines.at(i).selected) {
                ++selectedCount;
                lineSelected = true;
                if (selectedCount == 1) {
                    t = "x0: " + std::to_string(lines.at(i).x0) + ", y0: " + std::to_string(lines.at(i).y0)
                        + "\nx1: " +
                        std::to_string(lines.at(i).x1) + ", y1: " + std::to_string(lines.at(i).y1) + "\n\n";
                    strcpy(info, lines.at(i).infol);
                }
            }
            if (!circleSelected && !squareSelected && !triangleSelected) {
                lines.at(i).run();
            }
            else {
                lines.at(i).unselect(true);
            }
            if (lines.at(i).selected && colorize) {
                lines.at(i).color = selectionColor;
            }
            if (lines.at(i).selected && IsKeyPressed(KEY_DELETE)) {
                --selectedCount;
                lineSelected = false;
                lines.erase(lines.begin() + i);
            }
        }
        // detect the closest line to click and unselect other
        for (int i = 0; i < lines.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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
        if(lineSelected) t = t + std::to_string(deltasOfLinesToMouse[minIndex]) + " " + lines.at(minIndex).name;
        char const* displayCoordinates = t.c_str();
        for (int i = 0; i < lines.size(); i++) {
            if (i == minIndex) {
                continue;
            }
            lines.at(i).unselect(true);
        }
        BeginDrawing();

        // UI elements - library functions
        ClearBackground(RAYWHITE);
        DrawText("draw item from menue to canvas with a click of a mouse, \nmove it with pressed mouse, \ncolor it by selecting it with a click of a mouse and clicking on color from menue, \nset rotation, translation, sheering and scale to selected item(s) from menue, \nto delete select element and press delete key", screenBorder, screenBorder, controlsSize, DARKGRAY);
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
        Color color1 = GetColor(0xe0119a);
        Color color2 = GetColor(0xffeb00);
        DrawRectangleGradientH(fillButton.x, fillButton.y, fillButton.width, fillButton.height, PINK, YELLOW);
        DrawText("F", fillButton.x+3, fillButton.y+1, fillButton.width, BLACK);
        DrawRectangleLines(clearButton.x, clearButton.y, clearButton.width, clearButton.height, BLACK);
        DrawText("C", clearButton.x + 3, clearButton.y + 1, clearButton.width, BLACK);

        
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
        // circles
        for (int i = 0; i < circles.size(); i++) {
            circles.at(i).draw(circles.at(i).xm, circles.at(i).ym, circles.at(i).r);
            if (circles.at(i).selected) {
                DrawRectangleLines(circles.at(i).xm - circles.at(i).r, circles.at(i).ym - circles.at(i).r, 
                    circles.at(i).r * 2, circles.at(i).r * 2, GREEN);
            }
        }
        // triangles
        for (int i = 0; i < triangles.size(); i++) {
            triangles.at(i).draw();
            if (triangles.at(i).selected) {
                DrawRectangleLines(triangles.at(i).borderX, triangles.at(i).borderY, triangles.at(i).borderW, 
                    triangles.at(i).borderH, GREEN);
            }
        }
        // squares
        for (int i = 0; i < squares.size(); i++) {
            squares.at(i).draw();
            if (squares.at(i).selected) {
                DrawRectangleLines(squares.at(i).x0 - controlsSize/2, squares.at(i).y0 - controlsSize / 2, 
                    squares.at(i).x3 - squares.at(i).x0 + controlsSize, squares.at(i).y1 - squares.at(i).y0 + controlsSize, GREEN);
            }
        }
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context    
    return 0;
}