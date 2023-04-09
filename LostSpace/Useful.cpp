#include "Useful.h"
#include "Globals.h"

void SetConsoleSize(int w, int h)
{
	CONSOLE_SCREEN_BUFFER_INFOEX consolesize;

	consolesize.cbSize = sizeof(consolesize);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfoEx(hConsole, &consolesize);

	COORD c;
	c.X = w;
	c.Y = h;
	consolesize.dwSize = c;

	consolesize.srWindow.Left = 0;
	consolesize.srWindow.Right = w;
	consolesize.srWindow.Top = 0;
	consolesize.srWindow.Bottom = h;

	SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
}

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

void PrettyPrint(string& input)
{
	unsigned int bufferCount = 0;

	stringstream ss(input);
	string word, line;

	while(getline(input, line))
	{
		std::stringstream linestream(line);

		copy(std::istream_iterator<std::string>(linestream),
			std::istream_iterator<std::string>(),
			std::back_inserter(words));

		++lineCount;
	}

	while (ss >> word)
	{
		if (bufferCount + word.size() >= CONSOLE_WIDTH - 1)
		{
			printf("\n");

			bufferCount = 0;
		}

		printf("%s", &word[0]);

		if (word != "\n")
		{
			printf(" ");

			bufferCount += word.size() + 1;
		}
		else
		{
			cout << "------------- ENTERS -------- " << endl;
		}
	}

	printf("\n");
}

string FirstLetterUpper(const string& text)
{
	string upperFirst = text;
	upperFirst[0] = toupper(upperFirst[0]);

	return upperFirst;
}