#include "home.hpp"

Rectangle textBox3 = { 100, 300, 240, 40 };
Rectangle textBox4 = { 100, 380, 240, 40 };
Rectangle textBox5 = { 100, 450, 240, 40 };
char text3[25] = { 0 }; // Text for the third text box
char text4[25] = { 0 }; // Text for the fourth text box
char text5[25] = { 0 }; // Text for the fifth text box
int textSize3 = 0, textSize4 = 0, textSize5 = 0;
bool isTextBox3Focused = false, isTextBox4Focused = false, isTextBox5Focused = false;
int framesCounterHome = 0;
bool cursorVisibleHome = true;

void drawTextBoxes() {
    DrawTextBox(textBox3.x, textBox3.y, isTextBox3Focused, "Username:", text3);
    DrawTextBox(textBox4.x, textBox4.y, isTextBox4Focused, "Confirm Password:", text4);
    DrawTextBox(textBox5.x, textBox5.y, isTextBox5Focused, "Sum:", text5);

    if (isTextBox3Focused) {
        handleTextBoxInput(text3, textSize3);
    }
    else if (isTextBox4Focused) {
        handleTextBoxInput(text4, textSize4);
    }
    else if (isTextBox5Focused) {
        handleTextBoxInput(text5, textSize5);
    }
}

void handleTextBoxInput(char* text, int& textSize) {
    // Handle text input for the focused textbox
    framesCounterHome++;
    if (framesCounterHome >= 30) {
        framesCounterHome = 0;
        cursorVisibleHome = !cursorVisibleHome;
    }

    int key = GetKeyPressed();
    if (key != 0) {
        // Handle key presses for the focused textbox
        if ((key >= 32) && (key < 127) && (textSize < 19)) {
            // Convert the key to lowercase
            key = tolower(key);

            text[textSize] = (char)key;
            textSize++;
        }
        else if (key == KEY_BACKSPACE && textSize > 0) {
            textSize--;
            text[textSize] = '\0';
        }
    }
}

int home(const string& username, const string& password, double& balance) {
    SetTargetFPS(60);

    Texture2D nav = LoadTexture("Images/Bar.png");
    Texture2D backg = LoadTexture("Images/background.png");

    Rectangle Balance = { 380, 10, 115, 30 }, Transac = { 520, 10, 195, 30 }, Will = { 748, 10, 64, 30 };

    bool Bal = true, Trans = false, Wil = false;

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
            drawTextBoxes();
        }
        else
            DrawText("Transactions", 520, 10, 28, WHITE);
        if (Wil) {
            isRecPressed(Balance, Bal);
            isRecPressed(Transac, Trans);
            if (Bal or Trans)
                Wil = false;
            DrawText("Wills", 750, 10, 28, GRAY);
        }
        else
            DrawText("Wills", 750, 10, 28, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}