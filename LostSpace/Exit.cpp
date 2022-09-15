#include "Exit.h"
#include "Room.h"

Exit::Exit
(
	const string& name,
	const string& description,
	const string& openDesc,
	Direction direction,
	Room* source,
	Room* destination,
	bool locked,
	Item* key
) : Entity(name, description, (Entity*)source)
{
	this->type = Type::EXIT;
	this->openDesc = openDesc;
	this->direction = direction;
	this->source = source;
	this->destination = destination;
	this->locked = locked;
	this->key = key;
}

Exit::~Exit(){}

void Exit::Look(const Room* room) const
{
	if (!Locked())
	{
		if (DoorDirection(room) == "up")
		{
			cout << "On the cieling there's an opened " << this->name << ". "
				<< this->openDesc << endl;
		}
		else if (DoorDirection(room) == "down")
		{
			cout << "On the floor there's an opened " << this->name << ". "
				<< this->openDesc << endl;
		}
		else {
			cout << "To the " << DoorDirection(room) << " there's an opened " << this->name << ". "
				<< this->openDesc << endl;
		}
	}
	else
	{
		if (DoorDirection(room) == "up") 
		{
			cout << "On the cieling there's a closed " << this->name << ". "
				<< this->description << endl;
		}
		else if (DoorDirection(room) == "down")
		{
			cout << "On the floor there's a closed " << this->name << ". "
				<< this->description << endl;
		}
		else {
			cout << "To the " << DoorDirection(room) << " there's a closed " << this->name << ". "
				<< this->description << endl;
		}
	}
}

void Exit::Unlock(const Item* item)
{
	if (item == this->key)
	{
		if (Locked())
		{
			this->locked = false;
			cout << "The " << this->name << " is unlocked" << endl;
		}
		else cout << "The " << this->name << " is already unlocked" << endl;
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