#include "mainMenu.hpp"
using namespace std;

Rectangle Login = { screenWidth / 2 - 80, 400, 170, 45 }, Register = { screenWidth / 2 - 50, 450, 160, 40 };
Texture2D NavBar, background, blockBG, login, regis;
char text1[25] = { 0 }; // Text for the first text box
char text2[25] = { 0 };
char pass[25] = { 0 };// Text for the second text box
int textSize1 = 0, textSize2 = 0;
bool isTextBox1Focused = false, isTextBox2Focused = false;
int framesCounter = 0;
double USINGbalance;
bool cursorVisible = true, check = false;
bool loginPressed = false, registerPressed = false, flag = false, willFlag = false;
string username, password, usernameFromFile, passwordFromFile, balanceFromFile, USINGpass;
fstream Usernames, Passwords, Balances;
Rectangle textBox1 = { screenWidth / 2 - 120, screenHeight / 2 - 95, 240, 40 };
Rectangle textBox2 = { screenWidth / 2 - 120, screenHeight / 2 - 15, 240, 40 };
string dataFolderPath = "Data";

void isRecPressed(Rectangle rec, bool& check) {
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            check = true;
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

        if (isTextBox1Focused && (key >= 32) && (key < 127) && (textSize1 < 19)) {
            text1[textSize1] = (char)key;
            textSize1++;
            text1[textSize1 - 1] = tolower(text1[textSize1 - 1]);
            username = string(text1);
        }
        else if (isTextBox1Focused && key == KEY_BACKSPACE && textSize1 > 0) {
            textSize1--;
            text1[textSize1] = '\0';
            text1[textSize1 - 1] = tolower(text1[textSize1 - 1]);
            username = string(text1);
        }
        else if (isTextBox2Focused && (key >= 32) && (key < 127) && (textSize2 < 19)) {
            text2[textSize2] = (char)key;
            pass[textSize2] = '*';
            textSize2++;
            text2[textSize2 - 1] = tolower(text2[textSize2 - 1]);
            password = string(text2);
        }
        else if (isTextBox2Focused && key == KEY_BACKSPACE && textSize2 > 0) {
            textSize2--;
            text2[textSize2] = '\0';
            pass[textSize2] = '\0';
            text2[textSize2 - 1] = tolower(text2[textSize2 - 1]);
            password = string(text2);
        }
    }
}


void ReadFiles() {
    // Open files for reading
    Usernames.open(dataFolderPath + "/usernames.txt", ios::in);
    Passwords.open(dataFolderPath + "/passwords.txt", ios::in);
    Balances.open(dataFolderPath + "/balances.txt", ios::in);

    if (!Usernames.is_open() || !Passwords.is_open() || !Balances.is_open()) {
        cerr << "Error opening one or more files." << endl;
    }
}
bool CheckCredentials() {
    // Open files for reading
    Usernames.open(dataFolderPath + "/usernames.txt", ios::in);
    Passwords.open(dataFolderPath + "/passwords.txt", ios::in);
    Balances.open(dataFolderPath + "/balances.txt", ios::in);

    // Read usernames, passwords, and balances and compare with entered credentials
    while (getline(Usernames, usernameFromFile) && getline(Passwords, passwordFromFile) && getline(Balances, balanceFromFile))
    {
        if (usernameFromFile == username && passwordFromFile == password) {
            cout << "Entered Username: " << username << endl;
            cout << "Entered Password: " << password << endl;
            USINGuser = username;
            USINGpass = password;
            USINGbalance = stod(balanceFromFile); // Convert balance to double
            Usernames.close();
            Passwords.close();
            Balances.close();
            return true; // Credentials match
        }
    }

    Usernames.close();
    Passwords.close();
    Balances.close();

    return false; // Credentials do not match
}


void WriteFiles() {
    // Open files in append mode to keep existing data
    bool checkIfAlreadyRegistered = false;
    Usernames.open(dataFolderPath + "/usernames.txt", ios::app && ios::in);
    Passwords.open(dataFolderPath + "/passwords.txt", ios::app);
    Balances.open(dataFolderPath + "/balances.txt", ios::app);

    if (Usernames.is_open() && Passwords.is_open() && Balances.is_open() && registerPressed) {
        while (getline(Usernames, usernameFromFile)) {
            if (username == usernameFromFile) {
                cout << "This username has already been used!" << endl;
                checkIfAlreadyRegistered = true;
                registerPressed = false;
            }
        }
        if (!checkIfAlreadyRegistered) {
            Usernames << username << endl;
            Passwords << password << endl;
            Balances << "100.0" << endl; //Starting balance = 100
            cout << "Registered successfully!" << endl;
            Usernames.close();  // Close immediately after writing
            Passwords.close();
            Balances.close();
            registerPressed = false;
        }

    }
}

void DrawTextBox(float x, float y, bool& isFocused, const char* labelText, char* text, bool check, bool isInWill) {
    Rectangle rect;
    if (!check) {
        rect = { x, y, 240, 40 }; // Standard text box size
    }
    else {
        rect = { x, y, 500, 400 }; // Adjusted will text box size
    }

    DrawRectangleRec(rect, isFocused ? GRAY : LIGHTGRAY);
    DrawRectangleLinesEx(rect, 2.5, isFocused ? DARKGRAY : DARKGRAY);

    DrawText(labelText, x, y - 30, 20, WHITE);

    // Adjust cursorX calculation based on isInWill
    int cursorX = x + 7 + MeasureText(text, 20) + 5;

    DrawText(text, x + 7, y + 10, 20, BLACK);

    if (isFocused && cursorVisible) {
        DrawLine(cursorX, y + 10, cursorX, y + 27, WHITE);
    }

    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isFocused = !isFocused;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isFocused = false;
    }
}

void DrawLoginBoxes() {
    DrawTextBox(screenWidth / 2 - 120, screenHeight / 2 - 95, isTextBox1Focused, "Username:", text1, check, willFlag);
    DrawTextBox(screenWidth / 2 - 120, screenHeight / 2 - 15, isTextBox2Focused, "Password:", pass, check, willFlag);

    if (isTextBox1Focused || isTextBox2Focused) {
        HandleTextInput();
    }
    else {
        framesCounter = 0;
        cursorVisible = true;
    }
}

void UnloadTexts() {
    UnloadTexture(NavBar);
    UnloadTexture(background);
    UnloadTexture(blockBG);
    UnloadTexture(login);
    UnloadTexture(regis);
}

void loginAndregisterProcess() {
    if (loginPressed) {
        if ((textSize1 == 0) || (textSize2 == 0)) {
            cout << "Invalid credentials: Empty fields" << endl;
        }
        else {
            if (CheckCredentials()) {
                cout << "Login successful! Welcome, " << USINGuser << ". Your balance: " << USINGbalance << endl;
                UnloadTexts();
                home(USINGuser, USINGpass, USINGbalance); // Pass the balance to the home function
            }
            else {
                cout << "Invalid credentials: Username or password incorrect" << endl;
            }
        }
        loginPressed = false;
    }
    if (registerPressed) {
        WriteFiles();
    }
}

void DrawApp() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(NavBar, -10, 0, RAYWHITE);
    DrawTexture(background, 0, 50, RAYWHITE);
    DrawTexture(blockBG, screenWidth / 2 - blockBG.width / 2, screenHeight / 2 - blockBG.height / 2, RAYWHITE);
    DrawTexture(login, screenWidth / 2 - 80, 400, RAYWHITE);
    DrawTexture(regis, screenWidth / 2 - 50, 450, RAYWHITE);
    DrawLoginBoxes();

    loginAndregisterProcess();
    if(!loginPressed)
        EndDrawing();
}

int main() {
    InitApp();
    while (!WindowShouldClose()) {
        isRecPressed(Login, loginPressed);
        isRecPressed(Register, registerPressed);
        DrawApp();
    }
    return 0;
}