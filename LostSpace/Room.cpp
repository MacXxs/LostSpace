#include "Room.h"
#include "Exit.h"
#include "Consumable.h"

Room::Room(
	const string& name, 
	const string& description, 
	bool lighten,
	bool lightState,
	string darkDescription) : 
	Entity(name, description, NULL)
{
	this->type = Type::ROOM;
	this->lighten = lighten;
	this->darkDescription = darkDescription;
	this->lightState = lightState;
}

Room::~Room(){}

void Room::Look() const
{
	TextColor(BRIGHT_GREEN);
	cout << "==== " << this->name << " ====" << endl;
	TextColor(GREEN);

	if (Illuminated()) cout << this->description << endl;
	else cout << this->darkDescription << endl;

	// List everything in the room
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); it++)
	{
		if ((*it)->type == Type::ITEM && Illuminated())
		{
			cout << "There is an item in this room: ";
			if (((Item*)(*it))->itemType == ItemType::CONSUMABLE)
			{

				((Consumable*)(*it))->Look();
			}
			else (*it)->Look();
		}
		else if ((*it)->type == Type::EXIT)
		{
			Exit* exit = (Exit*)(*it);
			exit->Look(this);
		}
		else if ((*it)->type == Type::CREATURE)
		{
			if ((*it)->type != Type::PLAYER)
			{
				(*it)->Look();
			}
		}
	}
}

bool Room::Illuminated() const
{
	return this->lighten == true;
}