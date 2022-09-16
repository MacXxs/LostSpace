#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Exit.h"
#include <vector>

class Item;
class Weapon;

class Player : public Creature
{

public:
	Player(
		const string& name, 
		const string& description, 
		const string& ripDescription,
		Room* location, 
		const int& health = MAX_HEALTH,
		const int& baseDamage = 10,
		const double& armor = 0,
		Creature* target = NULL
	);
	~Player();

	void Look(const vector<string>& input) const;
	void Open(const vector<string>& input) const;
	void Grab(const vector<string>& input);
	void Place(const vector<string>& input);
	void Drop(const vector<string>& input);
	void Use(const vector<string>& input);
	void Go(const vector<string>& input);
	void Consume(const vector<string>& input);
	void Update();
	void Attack();
	void AttackWithWeapon(Weapon* weapon);
	void Attack(vector<string>& input);
	void Attacked(const int& damage);

	void Inventory() const;
	bool BackpackEquipped() const;
	void AddItemToBackpack(Item* item);
	Item* GetItemFromBackpack(const string& name);
};
#endif // !PLAYER_H
