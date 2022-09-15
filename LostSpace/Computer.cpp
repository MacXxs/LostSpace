#include "Computer.h"

Computer::Computer
(
	const string& name,
	const string& description,
	Entity* location,
	const bool& container,
	const bool& grabable,
	const int&,
	const string & onText,
	const string& offText,
	const string& validation,
	const string& error
) : Item(name, description, location, container, spaces, grabable)
{
	this->itemType = ItemType::COMPUTER;
}

Computer::~Computer() {}

void Computer::Look() const
{
	Item::Look();
}

void Computer::Use() const
{

}