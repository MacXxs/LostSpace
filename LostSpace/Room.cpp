#include "Room.h"
#include "Exit.h"

Room::Room(const string& name, const string& description) : 
	Entity(name, description, NULL)
{
	this->type = Type::ROOM;
}

Room::~Room(){}

void Room::Look() const
{
	cout << "---- " << this->name << " ----" << endl;
	cout << this->description << endl;

	// List everything in the room
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); it++)
	{
		if ((*it)->type == Type::ITEM)
		{
			cout << "There is something on this room: " << (*it)->description << endl;
		}
		else if ((*it)->type == Type::EXIT)
		{
			Exit* exit = (Exit*)(*it);
			exit->Look(this);
		}
	}
}