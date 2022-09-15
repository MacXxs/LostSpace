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
	Exit* exit
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
}

Computer::~Computer() {}

void Computer::Look() const
{
	Item::Look();
}

void Computer::Use() const
{
	if (!this->done)
	{
		cout << this->offText << endl;
	}
	else cout << this->onText << endl;
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