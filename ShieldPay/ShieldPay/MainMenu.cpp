#include "mainMenu.hpp"

const int screenWidth = 1100;
const int screenHeight = 700;
Rectangle Login = { screenWidth / 2 + 210, 365, 170, 45 };
Texture2D NavBar, background, blockBG, login, regis;
char text1[21] = { 0 }; // Text for the first text box
char text2[21] = { 0 }; // Text for the second text box
int textSize1 = 0, textSize2 = 0;
bool isTextBox1Focused = false, isTextBox2Focused = false;
int framesCounter = 0;
bool cursorVisible = true;
bool loginPressed = false;
string username, password;
fstream Usernames, Passwords;

void isRecPressed(Rectangle rec) {
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            loginPressed = true;
        }
    }
}

void WriteFiles() {
    Usernames.open("Data/Usernames.txt", ios::out);
    Passwords.open("Data/Passwords.txt", ios::out);
    if (Usernames.is_open() && Passwords.is_open() && loginPressed) {
        Usernames << username << endl;
        Passwords << password << endl;
        Usernames.close();
        Passwords.close();
    }
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

void HandleTextInput() {
    framesCounter++;
    if (framesCounter >= 30) {
        framesCounter = 0;
        cursorVisible = !cursorVisible;
    }

    int key = GetKeyPressed();
    if (key != 0) {

        if (isTextBox1Focused && (key >= 32) && (key < 127) && (textSize1 < 16)) {
            text1[textSize1] = (char)key;
            textSize1++;
            
        }
        else if (isTextBox1Focused && key == KEY_BACKSPACE && textSize1 > 0) {
            textSize1--;
            text1[textSize1] = '\0';
            
        }
        else if (isTextBox2Focused && (key >= 32) && (key < 127) && (textSize2 < 16)) {
            text2[textSize2] = (char)key;
            textSize2++;
            
        }
        else if (isTextBox2Focused && key == KEY_BACKSPACE && textSize2 > 0) {
            textSize2--;
            text2[textSize2] = '\0';
            
        }
    }
    
}


void DrawTextBoxes() {
    // Define the first text box
    Rectangle textBox1 = { screenWidth / 2 + 180, screenHeight / 2 - 95, 240, 40 };
    DrawRectangleRec(textBox1, isTextBox1Focused ? SKYBLUE : LIGHTGRAY);
    DrawRectangleLinesEx(textBox1, 2, isTextBox1Focused ? DARKBLUE : DARKGRAY);

    DrawText(text1, screenWidth / 2 + 187, screenHeight / 2 - 85, 20, BLACK);
    DrawText("Username: ", screenWidth / 2 + 55, screenHeight / 2 - 85, 20, BLACK);
    if (isTextBox1Focused && cursorVisible) {
        int cursorX = screenWidth / 2 + 180 + MeasureText(text1, 20) + 20;
        DrawLine(cursorX - 10, screenHeight / 2 - 85, cursorX - 10, screenHeight / 2 - 68, BLACK);
    }

    if (CheckCollisionPointRec(GetMousePosition(), textBox1)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isTextBox1Focused = !isTextBox1Focused;
            string username(begin(text1), end(text1));
            cout << username << endl;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isTextBox1Focused = false;
        string username(begin(text1), end(text1));
        cout << username << endl;
    }

    // Define the second text box below the first one
    Rectangle textBox2 = { screenWidth / 2 + 180, screenHeight / 2 - 45, 240, 40 };
    DrawRectangleRec(textBox2, isTextBox2Focused ? SKYBLUE : LIGHTGRAY);
    DrawRectangleLinesEx(textBox2, 2, isTextBox2Focused ? DARKBLUE : DARKGRAY);

    DrawText(text2, screenWidth / 2 + 187, screenHeight / 2 - 35, 20, BLACK);
    DrawText("Password: ", screenWidth / 2 + 55, screenHeight / 2 - 35, 20, BLACK);
    if (isTextBox2Focused && cursorVisible) {
        int cursorX = screenWidth / 2 + 180 + MeasureText(text2, 20) + 20;
        DrawLine(cursorX - 10, screenHeight / 2 - 35, cursorX - 10, screenHeight / 2 - 15, BLACK);
    }

    if (CheckCollisionPointRec(GetMousePosition(), textBox2)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isTextBox2Focused = !isTextBox2Focused;
            string password(begin(text2), end(text2));
            cout << password << endl;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isTextBox2Focused = false;
        string password(begin(text2), end(text2));
        cout << password << endl;
    }

    if (isTextBox1Focused || isTextBox2Focused) {
        HandleTextInput();
    }
    else {
        framesCounter = 0;
        cursorVisible = true;
    }
}

void DrawApp() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(NavBar, 0, 0, RAYWHITE);
    DrawTexture(background, 0, 87, RAYWHITE);
    DrawTexture(blockBG, screenWidth / 2, 200, RAYWHITE);
    DrawTexture(login, screenWidth / 2 + 210, 365, RAYWHITE);
    DrawTexture(regis, screenWidth / 2 + 300, 420, RAYWHITE);
    DrawTextBoxes();
    if ((loginPressed && textSize1 == 0) || (loginPressed && textSize2 == 0)) {
        cout << "invalid credentials";
        loginPressed = false;
    }
    else if (loginPressed) {
        WriteFiles();
    }
    EndDrawing();
}

int main() {
    InitApp();
    while (!WindowShouldClose()) {
        isRecPressed(Login);
        DrawApp();
    }

    CloseWindow();
    return 0;
}





