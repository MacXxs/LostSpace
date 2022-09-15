#include <Windows.h>
#include "Item.h"

Item::Item
(
	const string& name,
	const string& description,
	Entity* parent,
	const bool& container,
	const int& spaces,
	const bool& grabable,
	const bool& lightSource) :
	Entity(name, description, parent)
{
	this->type = Type::ITEM;
	this->itemType = ItemType::ITEM;
	this->container = container;
	this->spaces = spaces;
	this->grabable = grabable;
	this->lightSource = lightSource;
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

bool Item::HasSpace() const
{
	return this->spaces > this->contains.size();
}

bool Item::IsALightSource() const
{
	return this->lightSource == true;
}