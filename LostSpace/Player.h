#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include <vector>

class Item;

class Player : public Creature
{

public:
	Player(const string& name, const string& description, Room* location, int health);
	~Player();

	void Look(const vector<string>& input) const;
	void Open(const vector<string>& input) const;
	void Grab(const vector<string>& input);
	void Place(const vector<string>& input);

	void Inventory() const;
	bool BackpackEquipped() const;
	void AddItemToBackpack(Item* item);
	Item* GetItemFromBackpack(const string& name);
};
#endif // !PLAYER_H
