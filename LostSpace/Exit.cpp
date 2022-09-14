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

 void Exit::Look() const
{
	if (!Locked())
	{
		cout << "To the " << DoorDirection() << " there's an opened " << this->name << ". "
			<< this->openDesc << endl;
	}
	else
	{
		cout << "To the " << DoorDirection() << " there's a closed " << this->name << ". "
			<< this->description << endl;
	}
}

bool Exit::Locked() const
{
	return this->locked == true;
}

string Exit::DoorDirection() const
{
	string dir;

	switch (this->direction)
	{
	case(Direction::NORTH):
		dir = "north";
		break;
	case(Direction::SOUTH):
		dir = "south";
		break;
	case(Direction::EAST):
		dir = "east";
		break;
	case(Direction::WEST):
		dir = "west";
		break;
	case(Direction::UP):
		dir = "up";
		break;
	case(Direction::DOWN):
		dir = "down";
		break;
	}

	return dir;
}