#include <iostream>
#include "Useful.h"
#include "World.h"
using namespace std;

int main()
{

    TextBig();
    TextColor(BRIGHT_GREEN);

    cout << "---------------------" << endl;
    cout << "---- Lost Space -----" << endl;
    cout << "---------------------\n" << endl;

    TextColor(GREEN);

    cout << "Welcome to Lost space!" << endl;
    cout << "The USG Not Ishimura explorer spacecraft is in searh for a new system with a \
habitable planet. \nDuring cryosleep something happens, our hero wakes up alone in the crew quarters \
after 100 years of slumber.\n" << endl;

    TextColor(WHITE);
    cout << "Type \"HELP\" for an oberview of the commands.\n" << endl;
    TextColor(GREEN);

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

