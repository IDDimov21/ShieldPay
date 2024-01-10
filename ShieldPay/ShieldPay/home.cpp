#include "home.hpp"

int home(const string& username) {
    SetTargetFPS(60);

    Texture2D nav = LoadTexture("Images/Bar.png");
    Texture2D backg = LoadTexture("Images/background.png");

    Rectangle Bal, Transac, Will;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(nav, -10, 0, RAYWHITE);
        DrawTexture(backg, 0, 50, RAYWHITE);

        DrawText(("Welcome, " + username).c_str(), 30, 10, 30, WHITE);
        DrawText("Balance", 350, 10, 28, WHITE);
        DrawText("Transactions", 550, 10, 28, WHITE);
        DrawText("Wills", 815, 10, 28, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}