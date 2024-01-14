#pragma once
#include "home.hpp"

const int screenWidth = 1100;
const int screenHeight = 700;

int main();
void InitApp();
void DrawApp();
void DrawLoginBoxes();
void HandleTextInput();
void DrawTextBox(float x, float y, bool& isFocused, const char* labelText, char* text, bool check, bool willText);
void isRecPressed(Rectangle rec, bool& check);
void ReadFiles();
void WriteFiles();
void loginAndregisterProcess();

