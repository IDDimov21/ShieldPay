
#include <iostream>
#include "raylib.h"

using namespace std;

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())   
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);


        EndDrawing();
    }
    CloseWindow();        

    return 0;
}

