#include "Item.h"

Item::Item
(
	const string& name,
	const string& description,
	Entity* location,
	bool container,
	bool grabable) :
	Entity(name, description, location)
{
	this->type = Type::ITEM;
	this->container = container;
	this->grabable = grabable;
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
	}
}

bool Item::IsGrabable() const
{
	bool grabable = this->grabable == true;
	
	if (!grabable) cout << "This isn't grabable" << endl;
	return grabable;
}