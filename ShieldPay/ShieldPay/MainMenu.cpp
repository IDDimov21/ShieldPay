#include "mainMenu.hpp"
using namespace std;

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
string dataFolderPath = "F:/ShieldPay/ShieldPay/ShieldPay/Data";

void isRecPressed(Rectangle rec) {
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            loginPressed = true;
        }
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
            text1[textSize1 - 1] = tolower(text1[textSize1 - 1]);
        }
        else if (isTextBox1Focused && key == KEY_BACKSPACE && textSize1 > 0) {
            textSize1--;
            text1[textSize1] = '\0';
            text1[textSize1 - 1] = tolower(text1[textSize1 - 1]);
        }
        else if (isTextBox2Focused && (key >= 32) && (key < 127) && (textSize2 < 16)) {
            text2[textSize2] = (char)key;
            textSize2++;
            text2[textSize2 - 1] = tolower(text2[textSize2 - 1]);
        }
        else if (isTextBox2Focused && key == KEY_BACKSPACE && textSize2 > 0) {
            textSize2--;
            text2[textSize2] = '\0';
            text2[textSize2 - 1] = tolower(text2[textSize2 - 1]);
        }
    }
}

void WriteFiles() {
    // Open files in append mode to keep existing data
    Usernames.open(dataFolderPath + "/usernames.txt", ios::out | ios::app);
    Passwords.open(dataFolderPath + "/passwords.txt", ios::out | ios::app);

    if (Usernames.is_open() && Passwords.is_open() && loginPressed) {
        Usernames << username << endl;
        Passwords << password << endl;
        Usernames.close();  // Close immediately after writing
        Passwords.close();  // Close immediately after writing
    }
}

void ReadFiles() {
    // Open files for reading
    Usernames.open(dataFolderPath + "/usernames.txt", ios::in);
    Passwords.open(dataFolderPath + "/passwords.txt", ios::in);

    if (!Usernames.is_open() || !Passwords.is_open()) {
        cerr << "Error opening username or password file." << endl;
        // Handle error appropriately
    }
}

bool CheckCredentials() {
    ReadFiles();

    string usernameFromFile, passwordFromFile;

    // Read usernames and passwords and compare with entered credentials
    while (getline(Usernames, usernameFromFile) && getline(Passwords, passwordFromFile)) {
        cout << "Entered Username: " << username << endl;
        cout << "Entered Password: " << password << endl;
        cout << "Stored Username: " << usernameFromFile << endl;
        cout << "Stored Password: " << passwordFromFile << endl;

        if (usernameFromFile == username && passwordFromFile == password) {
            Usernames.close();
            Passwords.close();
            return true; // Credentials match
        }
    }

    Usernames.close();
    Passwords.close();

    return false; // Credentials do not match
}

void DrawTextBoxes() {
    // Define the first text box
    Rectangle textBox1 = { screenWidth / 2 - 120, screenHeight / 2 - 95, 240, 40 };
    DrawRectangleRec(textBox1, isTextBox1Focused ? GRAY : LIGHTGRAY);
    DrawRectangleLinesEx(textBox1, 2.5, isTextBox1Focused ? DARKGRAY : DARKGRAY);

    DrawText("Username: ", screenWidth / 2 + -120, screenHeight / 2 - 125, 20, WHITE);
    DrawText(text1, screenWidth / 2 - 113, screenHeight / 2 - 85, 20, BLACK);
    if (isTextBox1Focused && cursorVisible) {
        int cursorX = screenWidth / 2 - 120 + MeasureText(text1, 20) + 20;
        DrawLine(cursorX - 10, screenHeight / 2 - 85, cursorX - 10, screenHeight / 2 - 65, WHITE);
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
    Rectangle textBox2 = { screenWidth / 2 - 120, screenHeight / 2 - 15, 240, 40 };
    DrawRectangleRec(textBox2, isTextBox2Focused ? GRAY : LIGHTGRAY);
    DrawRectangleLinesEx(textBox2, 2.5, isTextBox2Focused ? DARKGRAY : DARKGRAY);

    DrawText("Password: ", screenWidth / 2 - 120, screenHeight / 2 - 35, 20, WHITE);
    DrawText(text2, screenWidth / 2 - 113, screenHeight / 2 - 4, 20, WHITE);
    if (isTextBox2Focused && cursorVisible) {
        int cursorX = screenWidth / 2 - 120 + MeasureText(text2, 20) + 20;

        DrawLine(cursorX - 10, screenHeight / 2 - 5, cursorX - 10, screenHeight / 2 + 15, WHITE);

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

    DrawTexture(NavBar, -10, 0, RAYWHITE);
    DrawTexture(background, 0, 50, RAYWHITE);
    DrawTexture(blockBG, screenWidth / 2 - blockBG.width / 2, screenHeight / 2 - blockBG.height / 2, RAYWHITE);
    DrawTexture(login, screenWidth / 2 + 210, 365, RAYWHITE);
    DrawTexture(regis, screenWidth / 2 + 300, 420, RAYWHITE);
    DrawTextBoxes();

    if (loginPressed) {
        if ((textSize1 == 0) || (textSize2 == 0)) {
            cout << "Invalid credentials: Empty fields" << endl;
        }
        else {
            if (CheckCredentials()) {
                cout << "Login successful!" << endl;
            }
            else {
                cout << "Invalid credentials: Username or password incorrect" << endl;
            }
        }
        loginPressed = false;
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