#pragma once
#include <string>
#include "mainMenu.hpp"

using namespace std;

int home(const string& username, const string& passoword, double& balance);
void handleTextBoxInput(char* text, int& textSize);