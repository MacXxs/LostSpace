#include <iostream>

#include "Useful.h"
#include "World.h"
#include "Globals.h"

using namespace std;

int main()
{
    SetConsoleSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    TextBig();
    TextColor(BRIGHT_GREEN);

    cout << "---------------------" << endl;
    cout << "---- Lost Space -----" << endl;
    cout << "---------------------\n" << endl;

    TextColor(GREEN);

    PrettyPrint("Welcome to Lost space!\n\
The USG Not Ishimura explorer spacecraft is in searh for a new system with a \
habitable planet. \nDuring cryosleep something happens, our hero wakes up alone in the crew quarters \
after 100 years\nof slumber.\n");

    printf("\n");

    TextColor(WHITE);
    PrettyPrint("Type \"HELP\" for an oberview of the commands.\n");
    TextColor(GREEN);

    printf("\n");

    World ishimura;
   
    string input = "look";
    vector<string> inputArguments;
    
    while (true)
    {
        inputArguments = TreatInput(input);

        if (inputArguments.size() > 0 && inputArguments[0] == "quit")
        {
            break;
        }

        if (!ishimura.ValidCommand(inputArguments))
        {
            cout << "I beg your pardon?" << endl;
        }

        cout << "\n> ";
        TextColor(BLUE);
        getline(cin, input);
        TextColor(GREEN);
    }
    
    TextColor(WHITE);
}

