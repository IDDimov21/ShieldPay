#pragma once
#include <iostream>
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main();
void InitApp();
void DrawApp();
void DrawTextBoxes();
void HandleTextInput();
void isRecPressed(Rectangle rec, bool& check);
void ReadFiles();
void WriteFiles();