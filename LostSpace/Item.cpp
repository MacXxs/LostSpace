#include "Item.h"

Item::Item(const string& name, const string& description, Entity* location, bool container) :
	Entity(name, description, location)
{
	this->type = Type::ITEM;
	this->container = container;
}

Item::~Item() {}

void Item::Look() const
{
	if (this->contains.size() > 0)
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
	else
	{
		cout << "A " << this->name << ". " << this->description << endl;
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