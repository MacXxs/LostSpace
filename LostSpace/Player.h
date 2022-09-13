#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include <vector>

class Player : public Creature
{

public:
	Player(const string& name, const string& description, Room* location, int health);
	~Player();

	void Look(vector<string>& input) const;
	void Open(vector<string>& input) const;
	void Grab(vector<string>& input) const;
};
#endif // !PLAYER_H
