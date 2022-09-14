#include <Windows.h>
#include "Useful.h"
#include "Item.h"

Item::Item
(
	const string& name,
	const string& description,
	Entity* location,
	bool container,
	bool grabable,
	bool recorder,
	int spaces,
	const string& recording) :
	Entity(name, description, location)
{
	this->type = Type::ITEM;
	this->container = container;
	this->grabable = grabable;
	this->spaces = spaces;
	this->recording = recording;
}

Item::~Item() {}

void Item::Look() const
{
	Entity::Look();
}

void Item::Open() const
{
	cout << "You can find inside: " << endl;
	for (
		list<Entity*>::const_iterator it = this->contains.begin();
		it != this->contains.end(); it++
		)
	{
		cout << "\t- ";  (*it)->Look();
	}
}

void Item::Play() const
{
	string recording = this->recording;
	TextColor(RED);

	for (char& c : recording)
	{
		printf("%c",c);
		Sleep(35);
	}
	cout << '\n';

	TextColor(BRIGHT_GREEN);
}

bool Item::IsAContainer() const
{
	return this->container == true;
}

bool Item::IsEmpty() const
{
	if (this->IsAContainer())
	{
		return this->contains.size() == 0;
	}
	else
	{
		cout << "The " << this->name << " is not a contaier." << endl;
		return false;
	}
}

bool Item::IsGrabable() const
{
	bool grabable = this->grabable == true;
	
	if (!grabable) cout << "This isn't grabable" << endl;
	return grabable;
}

bool Item::IsARecorder() const
{
	return this->recorder == true;
}

bool Item::HasSapce() const
{
	return this->spaces > this->contains.size();
}