#pragma once
#include "home.hpp"
#include <iostream>
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int screenWidth = 1100;
const int screenHeight = 700;

int main();
void InitApp();
void DrawApp();
void DrawTextBoxes();
void HandleTextInput();
void isRecPressed(Rectangle rec, bool& check);
void ReadFiles();
void WriteFiles();
void loginAndregisterProcess();