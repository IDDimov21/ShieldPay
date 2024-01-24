#include "home.hpp"

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
Rectangle SaveButton = { 70, 580, 100, 40 };
Rectangle willTextBox = { 100, 300, 240, 100 };
int willTextSize = 0;
bool isWillTextBoxFocused = false;
string willTextString;
string USINGuser;

Rectangle textBoxRecipient = { screenWidth / 2 + 150, screenHeight / 2 - 150, 240, 40 };
char textRecipient[25] = { 0 };  // Text for the recipient's username text box
int textSizeRecipient = 0;
bool isTextBoxRecipientFocused = false;

string GetLoggedInUsername() {
    ifstream userFile("Usernames.txt");
    string loggedInUsername;
    if (userFile.is_open()) {
        getline(userFile, loggedInUsername);
        userFile.close();
    }
    return loggedInUsername;
}

void LoadWillFromFile(const string& username) {
    string filename = "Data/" + username + "_wills.txt";
    ifstream file(filename.c_str());
    if (file.is_open()) {
        // Read the entire contents of the file into willTextString
        string line;
        while (getline(file, line)) {
            willTextString += line + "\n";
        }
        file.close();

        // Set the loaded text into willText, ensuring null-termination
        willTextString.copy(willText, sizeof(willText) - 1);
        willText[willTextString.size()] = '\0';
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
            if ((key >= 32) && (key < 127) && (textSize < 99)) {
                key = tolower(key);

                if (textSize < 99) {
                    text[textSize] = (char)key;
                    textSize++;
                    text[textSize] = '\0';

                    str = string(text);
                }
            }
            else if (key == KEY_BACKSPACE && textSize > 0) {
                textSize--;
                text[textSize] = '\0';

                str = string(text);
            }
            else if (key == KEY_ENTER && textSize < 99) {
                // Handle Enter key press to add a new line
                text[textSize] = '\n';
                textSize++;
                text[textSize] = '\0';

                str = string(text);
            }
        }
        else if (isTextBoxRecipientFocused) {
            if ((key >= 32) && (key < 127) && (textSizeRecipient < 99)) {
                key = tolower(key);

                if (textSizeRecipient < 99) {
                    textRecipient[textSizeRecipient] = (char)key;
                    textSizeRecipient++;
                    textRecipient[textSizeRecipient] = '\0';

                    str = string(textRecipient);
                }
            }
            else if (key == KEY_BACKSPACE && textSizeRecipient > 0) {
                textSizeRecipient--;
                textRecipient[textSizeRecipient] = '\0';

                str = string(textRecipient);
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
    else{
            // Draw transparent gray block behind received wills
            DrawRectangle(willTextBox.x + willTextBox.width + 70, willTextBox.y - 100, 600, willTextBox.height + 20, Fade(GRAY, 0.5f));

            DrawTextBox(willTextBox.x, willTextBox.y - 100, isWillTextBoxFocused, "Your Will:", willText, willCheck, willText1);
            DrawText(willTextString.c_str(), willTextBox.x + willTextBox.width + 80, willTextBox.y - 80, 20, BLACK);
            DrawRectangleRec(SaveButton, isSendPressed ? RED : MAROON);
            DrawText("SAVE", SaveButton.x + 20, SaveButton.y + 10, 20, WHITE);
            DrawTextBox(textBoxRecipient.x, textBoxRecipient.y, isTextBoxRecipientFocused, "Recipient:", textRecipient, false, willText1);
    }
    if (isTextBoxRecipientFocused) {
        handleTextBoxInput(textRecipient, textSizeRecipient, willTextString, true);
    }
    else if (isWillTextBoxFocused) {
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


void SaveToFile(const char* text, const string& senderUsername, const string& recipientUsername) {
    // Save the will to the sender's file
    string senderFilename = "Data/" + senderUsername + "_wills.txt";
    ofstream senderFile(senderFilename.c_str());
    if (senderFile.is_open()) {
        cout << "Saving to file (sender): " << text << endl;  // Debug output
        senderFile << text << endl;
        senderFile.close();
    }

    // Save the will to the recipient's file
    string recipientFilename = "Data/" + recipientUsername + "_receivedwills.txt";
    ofstream recipientFile(recipientFilename.c_str(), ios::app);  // Append to existing file
    if (recipientFile.is_open()) {
        cout << "Saving to file (recipient): " << text << endl;  // Debug output
        recipientFile << text << endl;
        recipientFile.close();
    }
}

int home(const string& username, const string& password, double& balance) {
    SetTargetFPS(60);

    Texture2D nav = LoadTexture("Images/Bar.png");
    Texture2D backg = LoadTexture("Images/background.png");

    Rectangle Balance = { 380, 10, 115, 30 }, Transac = { 520, 10, 195, 30 }, Will = { 748, 10, 64, 30 };

    bool Bal = true, Trans = false, Wil = false;

    LoadWillFromFile(username);

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

                // Load received wills for the logged-in user
                string recipientFilename = "Data/" + username + "_receivedwills.txt";
                ifstream recipientFile(recipientFilename.c_str());
                string receivedWills;

                if (recipientFile.is_open()) {
                    string line;
                    while (getline(recipientFile, line)) {
                        receivedWills += line + "\n";
                    }
                    recipientFile.close();
                    willTextString = receivedWills;
                }
                else {
                    // Display "No received wills" if there are no received wills
                    willTextString = "No received wills";
                }

                // Draw text boxes and buttons
                drawTextBoxes();
                isRecPressed(SaveButton, isSendPressed);

                // Additional logic for the Save button
                if (isSendPressed) {
                    string recipientUsername = textRecipient;
                    SaveToFile(willText, username, recipientUsername);
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