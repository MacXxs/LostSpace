#include "Exit.h"

Exit::Exit
(
	const string& name,
	const string& description,
	const string& openDesc,
	Direction direction,
	Room* source,
	Room* destination,
	bool locked
) : Entity(name, description, (Entity*)source)
{
	this->type = Type::EXIT;
	this->openDesc = openDesc;
	this->direction = direction;
	this->source = source;
	this->destination = destination;
	this->locked = locked;
}

Exit::~Exit(){}

void Exit::Look(const Room* room) const
{
	if (!Locked())
	{
		cout << "To the " << DoorDirection(room) << " there's an opened " << this->name << ". "
			<< this->openDesc << endl;
	}
	else
	{
		cout << "To the " << DoorDirection(room) << " there's a closed " << this->name << ". "
			<< this->description << endl;
	}
}

void Exit::Unlock(const Item* item)
{
	if (item == this->key)
	{
		this->locked = false;
		cout << "The " << this->name << " is unlocked" << endl;
	}
	else cout << "The " << item->name << " can't open the " << this->name << "." << endl;
}

bool Exit::Locked() const
{
	return this->locked == true;
}

string Exit::DoorDirection(const Room* room) const
{
	string dir;

	switch (this->direction)
	{
	case(Direction::NORTH):
		if (room == this->source) dir = "north";
		else dir = "south";
		break;
	case(Direction::SOUTH):
		if (room == this->source) dir = "south";
		else dir = "north";
		break;
	case(Direction::EAST):
		if (room == this->source) dir = "east";
		else dir = "west";
		break;
	case(Direction::WEST):
		if (room == this->source) dir = "west";
		else dir = "east";
		break;
	case(Direction::UP):
		if (room == this->source) dir = "up";
		else dir = "down";
		break;
	case(Direction::DOWN):
		if (room == this->source) dir = "down";
		else dir = "up";
		break;
	}

	return dir;
}