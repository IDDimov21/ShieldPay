#include "home.hpp"

//char text1[25] = { 0 }; // Text for the first text box
//char text2[25] = { 0 }; // Text for the second text box
//int textSize1 = 0, textSize2 = 0;
//bool isTextBox1Focused = false, isTextBox2Focused = false, cursorVisible = true;
//string username;

//void DrawCredentialBoxes() {
//    Rectangle textBox1 = { screenWidth / 2 - 120, screenHeight / 2 - 95, 240, 40 };
//    DrawRectangleRec(textBox1, isTextBox1Focused ? GRAY : LIGHTGRAY);
//    DrawRectangleLinesEx(textBox1, 2.5, isTextBox1Focused ? DARKGRAY : DARKGRAY);
//    DrawText(text1, screenWidth / 2 - 113, screenHeight / 2 - 85, 20, BLACK);
//
//    if (isTextBox1Focused && cursorVisible) {
//        int cursorX = screenWidth / 2 - 120 + MeasureText(text1, 20) + 20;
//        DrawLine(cursorX - 10, screenHeight / 2 - 85, cursorX - 10, screenHeight / 2 - 65, WHITE);
//    }
//
//    if (CheckCollisionPointRec(GetMousePosition(), textBox1)) {
//        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//            isTextBox1Focused = !isTextBox1Focused;
//            string username(begin(text1), end(text1));
//        }
//    }
//    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//        isTextBox1Focused = false;
//        string username(begin(text1), end(text1));
//    }
//}

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
            DrawText("Username: ", 100, 320, 30, BLACK);
            DrawText("Confirm Password: ", 65, 390, 29, BLACK);
            DrawText("Sum: ", 135, 450, 30, BLACK);
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