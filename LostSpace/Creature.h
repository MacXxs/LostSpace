#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include "Room.h"
#include "Useful.h"

class Creature : public Entity
{

public:
	Room* parent;
	Creature* target;

	int health;
	int baseDamage;
	double armor;
	string ripDescription;

	Creature(
		const string& name,
		const string& description,
		const string& ripDescription,
		Room* location,
		const int& health = MAX_HEALTH,
		const int& baseDamage = 10,
		const double& armor = 0,
		Creature* target = NULL
	);
	~Creature();

	virtual void Look() const;
	virtual void Update();
	virtual void Attack();
	virtual void Attacked(const int& damage);

	void ScanForTarget();
	bool Dead() const;
	bool SameRoom(Creature* creature) const;
	Room* Location() const;
};

#endif // !CREATURE_H