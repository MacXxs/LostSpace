#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item
{
public:
	int damagePoints;

	Weapon(
		const string& name,
		const string& description,
		Entity* parent,
		const int& damagePoints = 10
		);

	~Weapon();
};
#endif // !WEAPON_H
