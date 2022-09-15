#include "Weapon.h"

Weapon::Weapon(
	const string& name,
	const string& description,
	Entity* parent,
	const int& damagePoints
	) : Item(name, description, parent)
{
	this->itemType = ItemType::WEAPON;
	this->damagePoints = damagePoints;
}

Weapon::~Weapon() {};