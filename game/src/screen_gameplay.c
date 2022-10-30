/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static int x0 = 113; static int y0 = 112; static int x1 = 250; static int y1 = 150;



//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER)) //  || IsGestureDetected(GESTURE_TAP)
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}
void paintingWithABrush(int x, int y) {
    DrawPixel(x, y, WHITE);
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    DrawTextEx(font, "GAMEPLAY SCREEN", (Vector2){ 20, 10 }, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

    Vector2 p1 = (Vector2){ 100, 50 };
    Vector2 p2 = (Vector2){ 100, 150 };
    Vector2 p3 = (Vector2){ 50, 100 };
    Vector2 p4 = (Vector2){ 150, 100 };

    DrawLineV(p1, p2, GREEN);
    DrawLineV(p3, p4, GREEN);
    DrawPixelV(p1, WHITE);
    DrawPixelV(p2, WHITE);
    DrawPixelV(p3, WHITE);
    DrawPixelV(p4, WHITE);


    // if resizing line
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        paintingWithABrush(GetMouseX(), GetMouseY());
        x1 = GetMouseX();
        y1 = GetMouseY();
        DrawText("PRESSed left button of a mouse", 150, 420, 20, MAROON);
    }
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
    for (;;) {  /* loop */
        DrawPixel(x0, y0, GREEN);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}