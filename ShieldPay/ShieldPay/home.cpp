#include "home.hpp"
#include <sstream>
Rectangle textBox3 = { 100, 300, 240, 40 }, textBox4 = { 100, 380, 240, 40 }, textBox5 = { 100, 450, 240, 40 };
Rectangle Send = { 165, 520, 100, 40 };
char text3[25] = { 0 }; // Text for the third text box
char text4[25] = { 0 }; // Text for the fourth text box
char text5[25] = { 0 }; // Text for the fifth text box
int textSize3 = 0, textSize4 = 0, textSize5 = 0;
bool isTextBox3Focused = false, isTextBox4Focused = false, isTextBox5Focused = false, NumCheck = true;
bool cursorVisibleHome = true, isSendPressed = false, willCheck = false;
char willText[100] = { 0 };
bool willText1 = false;
int framesCounterHome = 0;
string dataFolder = "/Data";
string user, sum, pass;
Rectangle SaveButton = { 165, 580, 100, 40 };
Rectangle willTextBox = { 100, 300, 400, 200 };
int willTextSize = 0;
bool isWillTextBoxFocused = false;
string willTextString;
string USINGuser;

string GetLoggedInUsername() {
    ifstream userFile("Usernames.txt");
    string loggedInUsername;
    if (userFile.is_open()) {
        getline(userFile, loggedInUsername);
        userFile.close();
    }
    return loggedInUsername;
}

void LoadWillFromFile() {
    string loggedInUsername = GetLoggedInUsername();
    cout << loggedInUsername;
    string filename = "Data/" + loggedInUsername + "_wills.txt";
    ifstream file(filename.c_str());
    if (file.is_open()) {
        // Read the entire contents of the file into willTextString
        stringstream buffer;
        buffer << file.rdbuf();
        willTextString = buffer.str();
        file.close();
    }
}

void handleTextBoxInput(char* text, int& textSize, string& str, bool flag) {
    framesCounterHome++;
    if (framesCounterHome >= 30) {
        framesCounterHome = 0;
        cursorVisibleHome = !cursorVisibleHome;
    }

    int key = GetKeyPressed();
    if (key != 0) {
        // Handle key presses for the focused textbox
        if (flag) {
            if ((key >= 32) && (key < 127) && (textSize < 19)) {
                // Convert the key to lowercase
                key = tolower(key);

                text[textSize] = (char)key;
                textSize++;
                str = string(text);
            }
            else if (key == KEY_BACKSPACE && textSize > 0) {
                textSize--;
                text[textSize] = '\0';
                str = string(text);
            }
        }
        else {
            if ((key >= 32) && (key < 127) && (textSize < 19)) {
                // Convert the key to lowercase
                key = tolower(key);

                text[textSize] = (char)key;
                textSize++;
                str = string(text);
            }
            else if (key == KEY_BACKSPACE && textSize > 0) {
                textSize--;
                text[textSize] = '\0';
                str = string(text);
            }
        }
    }
}


void drawTextBoxes() {
    if (!willCheck) {
        DrawTextBox(textBox3.x, textBox3.y, isTextBox3Focused, "Username:", text3, willCheck, willText1);
        DrawTextBox(textBox4.x, textBox4.y, isTextBox4Focused, "Confirm Password:", text4, willCheck, willText1);
        DrawTextBox(textBox5.x, textBox5.y, isTextBox5Focused, "Sum:", text5, willCheck, willText1);
    }
    else {
        DrawTextBox(willTextBox.x, willTextBox.y, isWillTextBoxFocused, "Your Will:", willText, willCheck, willText1);
        DrawRectangleRec(SaveButton, isSendPressed ? RED : MAROON);
        DrawText("SAVE", SaveButton.x + 20, SaveButton.y + 10, 20, WHITE);
    }
    if (isWillTextBoxFocused) {
        handleTextBoxInput(willText, willTextSize, willTextString, true);
    }
    else if (isTextBox3Focused) {
        NumCheck = true;
        handleTextBoxInput(text3, textSize3, user, NumCheck);
    }
    else if (isTextBox4Focused) {
        NumCheck = true;
        handleTextBoxInput(text4, textSize4, pass, NumCheck);
    }
    else if (isTextBox5Focused) {
        NumCheck = false;
        handleTextBoxInput(text5, textSize5, sum, NumCheck);
    }
}


void SaveToFile(const char* text, const string& username) {
    string filename = "Data/" + username + "_wills.txt";
    ofstream file(filename.c_str());;
    if (file.is_open()) {
        cout << "Saving to file: " << text << endl;  // Debug output
        file << text << endl;
        file.close();
    }
}

int home(const string& username, const string& password, double& balance) {
    SetTargetFPS(60);
    
    Texture2D nav = LoadTexture("Images/Bar.png");
    Texture2D backg = LoadTexture("Images/background.png");

    Rectangle Balance = { 380, 10, 115, 30 }, Transac = { 520, 10, 195, 30 }, Will = { 748, 10, 64, 30 };

    bool Bal = true, Trans = false, Wil = false;

    LoadWillFromFile();  // Load existing will text

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(nav, -10, 0, RAYWHITE);
        DrawTexture(backg, 0, 50, RAYWHITE);
        DrawText(("User: " + username).c_str(), 50, 10, 30, WHITE);

        isRecPressed(Balance, Bal);
        isRecPressed(Transac, Trans);
        isRecPressed(Will, Wil);

        if (Bal) {
            isRecPressed(Transac, Trans);
            isRecPressed(Will, Wil);
            if (Trans or Wil)
                Bal = false;
            DrawText("Balance", 380, 10, 28, GRAY);
            DrawText("Welcome to ShieldPay, your online banking assistant!", 100, 180, 32, BLACK);
            DrawText("current Balance:", 180, 230, 35, BLACK);
            DrawText(TextFormat("%.2lf", balance), 485, 228, 45, LIME);
        }
        else
            DrawText("Balance", 380, 10, 28, WHITE);
        if (Trans) {
            isRecPressed(Balance, Bal);
            isRecPressed(Will, Wil);
            if (Bal or Wil)
                Trans = false;
            DrawText("Transactions", 520, 10, 28, GRAY);
            DrawText("Transmit money", 180, 220, 40, BLACK);
            DrawText("SEND", 165, 520, 32, BLACK);
            drawTextBoxes();
            isRecPressed(Send, isSendPressed);
            transaction(username, password, balance, isSendPressed, pass, user, sum, dataFolder);
        }
        else
            DrawText("Transactions", 520, 10, 28, WHITE);
        if (Wil) {
            isRecPressed(Balance, Bal);
            isRecPressed(Transac, Trans);
            if (Bal or Trans) {
                Wil = false;
            }
            else {
                DrawText("Wills", 750, 10, 28, GRAY);
                willCheck = true;
                willText1 = true;
                drawTextBoxes();
                isRecPressed(SaveButton, isSendPressed);

                // Additional logic for the Save button
                if (isSendPressed) {
                    SaveToFile(willText, username);
                    isSendPressed = false;
                }
            }
        }
        else {
            DrawText("Wills", 750, 10, 28, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}