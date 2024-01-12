#include "home.hpp"

int home(const string& username, double& balance) {
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