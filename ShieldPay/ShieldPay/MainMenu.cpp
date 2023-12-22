
#include <iostream>
#include "raylib.h"

using namespace std;

int main()
{
    const int screenWidth = 1100;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D NavBar = LoadTexture("Images/Bar.png");
    Texture2D background = LoadTexture("Images/background.png");
    Texture2D blockBG = LoadTexture("Images/blockBG.png");
    Texture2D login = LoadTexture("Images/login.png");
    Texture2D regis = LoadTexture("Images/register.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())   
    {

        BeginDrawing();
        DrawTexture(NavBar, 0, 0, RAYWHITE);
        DrawTexture(background, 0, 87, RAYWHITE);
        DrawTexture(blockBG, screenWidth / 2, 200, RAYWHITE);
        DrawTexture(login, screenWidth / 2 + 210, 365, RAYWHITE);
        DrawTexture(regis, screenWidth / 2 + 300, 420, RAYWHITE);
        ClearBackground(RAYWHITE);


        EndDrawing();
    }
    CloseWindow();        

    return 0;
}

