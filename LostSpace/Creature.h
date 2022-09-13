#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include "Room.h"

class Creature : public Entity
{

public:
	Room* location;
	int health;

	Creature(const string& name, const string& description, Room* location, int& health);
	~Creature();

	virtual void Look() const;
	bool Dead() const;
	Room* Location() const;
};

#endif // !CREATURE_H