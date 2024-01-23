#pragma once
#include <string>
#include <iostream>
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "mainMenu.hpp"
#include "transaction.hpp"
using namespace std;

int home(const string& username, const string& passoword, double& balance);
void handleTextBoxInput(char* text, int& textSize, string& str, bool flag);
void drawTextBoxes();
void SaveToFile(const char* text, const string& username, const string& recipientUsername);
void isRecPressed(Rectangle rec, bool& check);
extern std::string USINGuser;