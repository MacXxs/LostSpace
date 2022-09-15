#include "Computer.h"
#include "Exit.h"

Computer::Computer
(
	const string& name,
	const string& description,
	Entity* parent,
	const bool& container,
	const int& spaces,
	const bool& grabable,
	const bool& lightSource,
	const string& onText,
	const string& offText,
	const string& validation,
	const string& error,
	const bool& done,
	Item* key,
	Exit* exit,
	const bool& ending
) : Item(name, description, parent, container, spaces, grabable, lightSource)
{
	this->itemType = ItemType::COMPUTER;
	this->onText = onText;
	this->offText = offText;
	this->validation = validation;
	this->error = error;
	this->done = done;
	this->key = key;
	this->exit = exit;
	this->ending = ending;
}

Computer::~Computer() {}

void Computer::Look() const
{
	Item::Look();
}

void Computer::Use()
{

	if (this->ending)
	{
		cout << this->onText << endl;
		this->done = true;
	}
	else
	{
		if (!this->done)
		{
			cout << this->offText << endl;
		}
		else cout << this->onText << endl;
	}
}

void Computer::Use(const Item* key)
{
	if (key == this->key)
	{
		cout << this->validation << endl;
		if (this->exit != NULL)
		{
			this->exit->Unlock(this);
		}
		this->done = true;
	}
	else cout << this->error << endl;
}

void Computer::Update()
{
	if (this->ending && this->done)
	{
		Sleep(2500);

		string end = "\nYou sit on one of the pilot chairs while you look how the USG No Ishimura starts \
getting closer and closer to the closest start. The emergency lights start bipping and the \
temperature keeps getting higher and higher until you reach the point of no return.\nYou look \
behind and see how the diseased and destroyed body of that atrocity starts twitching, but then \
a sudden explosion throws you out throught the deck window and you see, from outer space, how your \
ship starts imploding as you loose all the air in your lungs until death takes you.\n\nYou've made \
it, you destroyed the No Ishimura and with it the alien, congratulations!";

		TextColor(BRIGHT_GREEN);
		TypewriterOuptut(end);
		TextColor(GREEN);

		// For not getting stucked with the text showingeverytime you type something while dead
		this->done = false; 
	}
}