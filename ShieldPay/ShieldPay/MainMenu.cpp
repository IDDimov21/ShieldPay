#include "mainMenu.hpp"
using namespace std;

const int screenWidth = 1100;
const int screenHeight = 700;

Texture2D NavBar, background, blockBG, login, regis;
char text[21] = { 0 };
int textSize = 0;
bool isTextBoxFocused = false;
int framesCounter = 0;
bool cursorVisible = true;

// Function prototypes
void InitApp();
void DrawApp();
void DrawTextBox();
void HandleTextInput();

int main() {
    InitApp();

    while (!WindowShouldClose()) {
        DrawApp();
    }

    CloseWindow();
    return 0;
}

void InitApp() {
    InitWindow(screenWidth, screenHeight, "ShieldPay");

    NavBar = LoadTexture("Images/Bar.png");
    background = LoadTexture("Images/background.png");
    blockBG = LoadTexture("Images/blockBG.png");
    login = LoadTexture("Images/login.png");
    regis = LoadTexture("Images/register.png");

    SetTargetFPS(60);
}

void DrawApp() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(NavBar, 0, 0, RAYWHITE);
    DrawTexture(background, 0, 87, RAYWHITE);
    DrawTexture(blockBG, screenWidth / 2, 200, RAYWHITE);
    DrawTexture(login, screenWidth / 2 + 210, 365, RAYWHITE);
    DrawTexture(regis, screenWidth / 2 + 300, 420, RAYWHITE);

    DrawTextBox();

    EndDrawing();
}

void DrawTextBox() {
    Rectangle textBox = { screenWidth / 2 + 180, screenHeight / 2 - 95, 240, 40 };
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
        HandleTextInput();
    }
    else {
        framesCounter = 0;
        cursorVisible = true;
    }
}

void HandleTextInput() {
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