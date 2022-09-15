#include "Creature.h"

Creature::Creature(const string& name, const string& description, Room* location, int& health) :
	Entity(name, description, location)
{
	this->type = Type::CREATURE;
	this->parent = location;
	this->health = health;
}

Creature::~Creature(){}

void Creature::Look() const
{
	if (!Dead())
	{
		cout << name << endl;
	}
	else
	{
		cout << name << "'s lifeless body" << endl;
	}
	cout << description << endl;
}

bool Creature::Dead() const
{
	return health <= 0;
}

Room* Creature::Location() const
{
	return parent;
}