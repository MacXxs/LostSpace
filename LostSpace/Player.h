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

	void Look(vector<string>& input) const;
	void Open(vector<string>& input) const;
	void Grab(vector<string>& input);
	bool BackpackEquipped() const;
	void AddItemToBackpack(Item* item);

};
#endif // !PLAYER_H
