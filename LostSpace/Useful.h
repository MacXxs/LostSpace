#ifndef USEFUL_H
#define USEFUL_H

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
using namespace std;

enum Color {WHITE=7, GREEN=2, BLUE=3, RED=4, YELLOW=6, BRIGHT_GREEN=10};
enum class Direction { NORTH, SOUTH, EAST, WEST, UP, DOWN };


void TextColor(const int& k);
void TextBig();
void TextNormal();
string InputToLower(string& text);
vector<string> TreatInput(string& input);
string GetDirection(const Direction& direction);
void TypewriterOuptut(string& text);

#endif // !USEFUL_H