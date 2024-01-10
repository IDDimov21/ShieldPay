#include "home.hpp"

int home(const std::string& username) {
    SetTargetFPS(60);

    Texture2D nav = LoadTexture("Images/Bar.png");
    Texture2D backg = LoadTexture("Images/background.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(nav, -10, 0, RAYWHITE);
        DrawTexture(backg, 0, 50, RAYWHITE);

        // Position the rectangle at the top right part of the screen

        // Display the username on the home page with updated position and size
        float fontSize = 10.0f;
        float textX = GetScreenWidth() / 2 - MeasureText(("Welcome, " + username).c_str(), fontSize) / 2 + 5 * 20;
        float textY = GetScreenHeight() / 4; // More upwards

        DrawText(("Welcome, " + username).c_str(), textX, textY, fontSize * 5, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}