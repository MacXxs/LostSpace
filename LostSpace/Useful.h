#ifndef USEFUL_H
#define USEFUL_H

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
using namespace std;

enum Color {WHITE=7, GREEN=2, RED=4, BRIGHT_GREEN=10};
enum class Direction { NORTH, SOUTH, EAST, WEST, UP, DOWN };


void TextColor(const int& k);
void TextBig();
void TextNormal();
string InputToLower(string& text);
vector<string> TreatInput(string& input);
string GetDirection(const Direction& direction);

#endif // !USEFUL_H