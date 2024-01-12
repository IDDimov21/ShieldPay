#include "home.hpp"
#include <iomanip>

int home(const string& username, double& balance) {
    SetTargetFPS(60);

    Texture2D nav = LoadTexture("Images/Bar.png");
    Texture2D backg = LoadTexture("Images/background.png");

    Rectangle balanceButton = { 350, 10, 200, 50 };
    Rectangle transactionsButton = { 550, 10, 200, 50 };
    Rectangle willsButton = { 815, 10, 200, 50 };

    bool isBalanceButtonClicked = false;
    bool isTransactionsButtonClicked = false;
    bool isWillsButtonClicked = false;
    double selectedAccountBalance = 0.0;
    Rectangle transferTextBox = { 200, 300, 200, 40 };
    char transferText[25] = { 0 };
    int transferTextSize = 0;
    bool isTextBoxFocused = false;

    bool isSendButtonClicked = false;

    ifstream usernamesFile("F:/ShieldPay/ShieldPay/ShieldPay/Data/usernames.txt");
    vector<string> allUsernames;

    string tempUsername;
    while (usernamesFile >> tempUsername) {
        allUsernames.push_back(tempUsername);
    }
    usernamesFile.close();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(nav, -10, 0, RAYWHITE);
        DrawTexture(backg, 0, 50, RAYWHITE);

        DrawText(("Welcome, " + username).c_str(), 30, 10, 30, WHITE);
        DrawText(TextFormat("%.2lf", balance), 200, 200, 50, WHITE);
        DrawText("Transactions", 550, 10, 28, WHITE);
        DrawText("Wills", 815, 10, 28, WHITE);

        // Draw transfer text box
        DrawRectangleRec(transferTextBox, isTextBoxFocused ? GRAY : LIGHTGRAY);
        DrawText("Transfer Amount:", 30, 305, 20, WHITE);
        DrawText(transferText, 205, 305, 20, BLACK);
        if (isTextBoxFocused) {
            int cursorX = 200 + MeasureText(transferText, 20) + 20;
            DrawLine(cursorX - 10, 305, cursorX - 10, 345, WHITE);
        }

        // Draw send button
        Rectangle sendButton = { 30, 350, 100, 40 };
        DrawRectangleRec(sendButton, isSendButtonClicked ? RED : GREEN);
        DrawText("Send", 45, 355, 20, WHITE);

        // Display all usernames
        for (size_t i = 0; i < allUsernames.size(); ++i) {
            Rectangle usernameButton = { 30, 50 + i * 50, 200, 40 };
            DrawRectangleRec(usernameButton, BLACK);

            // Check if a username button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), usernameButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                isBalanceButtonClicked = false;
                isTransactionsButtonClicked = false;
                isWillsButtonClicked = false;
                isTextBoxFocused = false;
                isSendButtonClicked = false;

                // Handle the selected username
                cout << "Selected Username: " << allUsernames[i] << endl;
            }

            DrawText(allUsernames[i].c_str(), 35, 55 + i * 50, 20, WHITE);
        }

        EndDrawing();

        // Handle button clicks
        if (CheckCollisionPointRec(GetMousePosition(), balanceButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isBalanceButtonClicked = true;
            isTransactionsButtonClicked = false;
            isWillsButtonClicked = false;
            isTextBoxFocused = false;
            isSendButtonClicked = false;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), transactionsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isBalanceButtonClicked = false;
            isTransactionsButtonClicked = true;
            isWillsButtonClicked = false;
            isTextBoxFocused = false;
            isSendButtonClicked = false;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), willsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isBalanceButtonClicked = false;
            isTransactionsButtonClicked = false;
            isWillsButtonClicked = true;
            isTextBoxFocused = false;
            isSendButtonClicked = false;
        }

        // Handle text box input
        if (CheckCollisionPointRec(GetMousePosition(), transferTextBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isTextBoxFocused = true;
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isTextBoxFocused = false;
        }

        if (isTextBoxFocused) {
            int key = GetKeyPressed();
            if (key != 0 && (key >= 48 && key <= 57) && transferTextSize < 19) {
                transferText[transferTextSize] = (char)key;
                transferTextSize++;
            }
            else if (key == KEY_BACKSPACE && transferTextSize > 0) {
                transferTextSize--;
                transferText[transferTextSize] = '\0';
            }
        }

        // Handle send button click
        if (CheckCollisionPointRec(GetMousePosition(), sendButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isSendButtonClicked = true;
            isBalanceButtonClicked = false;
            isTransactionsButtonClicked = false;
            isWillsButtonClicked = false;
            isTextBoxFocused = false;

            // Handle the send button click
            if (transferTextSize > 0) {
                double amountToTransfer = stod(transferText);

                // Check if the amount to transfer is valid and within the balance
                if (amountToTransfer > 0 && amountToTransfer <= balance) {
                    // Deduct the amount from your account
                    balance -= amountToTransfer;
                    ofstream balancesFile("F:/ShieldPay/ShieldPay/ShieldPay/Data/balances.txt", ios::trunc);
                    if (balancesFile.is_open()) {
                        balancesFile << fixed << setprecision(2) << balance << endl;
                        selectedAccountBalance += amountToTransfer;
                        balancesFile << fixed << setprecision(2) << selectedAccountBalance << endl;
                        balancesFile.close();
                        cout << "Amount sent successfully!" << endl;
                    }
                    else {
                        cerr << "Error updating balances.txt" << endl;
                    }
                }
                else {
                    cout << "Invalid amount or insufficient balance!" << endl;
                }

                // Clear the transfer text box
                transferTextSize = 0;
                transferText[0] = '\0';
            }
            else {
                cout << "Please enter a valid amount!" << endl;
            }
        }
    }

    CloseWindow();
    return 0;
}