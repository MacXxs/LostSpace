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

const int MAX_HEALTH = 100;
const int MAX_ARMOR = 100;

void SetConsoleSize(int w, int h);
void TextColor(const int& k);
void TextBig();
void TextNormal();
void TypewriterOuptut(string& text);
void PrettyPrint(string& input);

string InputToLower(string& text);
string GetDirection(const Direction& direction);
string FirstLetterUpper(const string& text);

vector<string> TreatInput(string& input);

#endif // !USEFUL_H