#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

class Player;

class Consumable : public Item
{
public:
	int healthRegen;
	double armorBoost;
	int boosDuration;
	bool used = false;
	string usedDescription;
	Player* consumedBy = NULL;

	Consumable(
		const string& name,
		const string& description,
		const string& usedDescription,
		Entity* parent,
		const int& healthRegen = 0,
		const double& armorBoost = 0,
		const int& boosDuration = 0
		);

	~Consumable();

	void Update();
	void Look();
	void Consume(Player* player);
};

#endif // !CONSUMABLE_H