#include "Useful.h"

/* ------ Console Modifications ------ */
void TextColor(const int &k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

void TextBig()
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.dwFontSize.X = 32;
    fontex.dwFontSize.Y = 32;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}

void TextNormal()
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.dwFontSize.X = 18;
    fontex.dwFontSize.Y = 18;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}

string InputToLower(string& text)
{
    for (int i = 0; i < text.size(); i++) text[i] = tolower(text[i]);
    return text;
}

vector<string> TreatInput(string& input)
{
    vector<string> inputArguments;

    input = InputToLower(input);

    stringstream ss(input);
    string word;
    
    while (ss >> word) inputArguments.push_back(word);
    return inputArguments;
}

string GetDirection(const Direction& direction)
{
	string dir;

	switch (direction)
	{
	case Direction::NORTH:
		dir = "north";
		break;
	case Direction::SOUTH:
		dir = "north";
		break;
	case Direction::EAST:
		dir = "east";
		break;
	case Direction::WEST:
		dir = "west";
		break;
	case Direction::UP:
		dir = "up";
		break;
	case Direction::DOWN:
		dir = "down";
		break;
	}

	return dir;
}

void TypewriterOuptut(string& text)
{
	for (char& c : text)
	{
		printf("%c", c);
		Sleep(35);
	}
	cout << '\n';
}

string FirstLetterUpper(const string& text)
{
	string upperFirst = text;
	upperFirst[0] = toupper(upperFirst[0]);

	return upperFirst;
}