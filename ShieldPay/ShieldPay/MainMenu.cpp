#include "mainMenu.hpp"
using namespace std;

//void Input() {
//    if (isTextBoxFocused && cursorVisible) {
//        int cursorX = MeasureText(text, 20) + 20;
//        DrawLine(cursorX, 20, cursorX, 40, BLACK);
//    }
//    if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
//        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//            isTextBoxFocused = !isTextBoxFocused;
//        }
//    }
//    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//        isTextBoxFocused = false;
//    }
//
//    if (isTextBoxFocused) {
//        framesCounter++;
//        if (framesCounter >= 30) {
//            framesCounter = 0;
//            cursorVisible = !cursorVisible;
//        }
//        int key = GetKeyPressed();
//        if (key != 0) {
//            if ((key >= 32) && (key < 127) && (textSize < 16)) {
//                text[textSize] = (char)key;
//                textSize++;
//            }
//            else if (key == KEY_BACKSPACE && textSize > 0) {
//                textSize--;
//                text[textSize] = '\0';
//            }
//        }
//    }
//
//    else {
//        framesCounter = 0;
//        cursorVisible = true;
//    }
//}

/*IM ON THAT GOOD KUSH AND ALCOHOL I GOT SOME DOWN BITCHES I CAN CALL IDK WHAT I WOULD W / O YALL*/
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

    char text[21] = { 0 };  // Array to store input text (plus one for the null terminator)
    int textSize = 0;        // Variable to keep track of text size
    bool isTextBoxFocused = false;
    int framesCounter = 0;
    bool cursorVisible = true;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())   
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(NavBar, 0, 0, RAYWHITE);
        DrawTexture(background, 0, 87, RAYWHITE);
        DrawTexture(blockBG, screenWidth / 2, 200, RAYWHITE);
        DrawTexture(login, screenWidth / 2 + 210, 365, RAYWHITE);
        DrawTexture(regis, screenWidth / 2 + 300, 420, RAYWHITE);

        Rectangle textBox = { screenWidth / 2 + 180, screenHeight / 2 - 95 , 240, 40 };
        DrawRectangleRec(textBox, isTextBoxFocused ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLinesEx(textBox, 2, isTextBoxFocused ? DARKBLUE : DARKGRAY);

        DrawText(text, screenWidth / 2 + 187, screenHeight / 2 - 85, 20, BLACK);

            if (isTextBoxFocused && cursorVisible) {
                int cursorX = MeasureText(text, 20) + 20;
                DrawLine(cursorX, 20, cursorX, 40, BLACK);
            }
            if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    isTextBoxFocused = !isTextBoxFocused;
                }
            }
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                isTextBoxFocused = false;
            }
        
            if (isTextBoxFocused) {
                framesCounter++;
                if (framesCounter >= 30) {
                    framesCounter = 0;
                    cursorVisible = !cursorVisible;
                }
                int key = GetKeyPressed();
                if (key != 0) {
                    if ((key >= 32) && (key < 127) && (textSize < 16)) {
                        text[textSize] = (char)key;
                        textSize++;
                    }
                    else if (key == KEY_BACKSPACE && textSize > 0) {
                        textSize--;
                        text[textSize] = '\0';
                    }
                }
            }
        
            else {
                framesCounter = 0;
                cursorVisible = true;
            }

        EndDrawing();
    }
    CloseWindow();        

    return 0;
}

