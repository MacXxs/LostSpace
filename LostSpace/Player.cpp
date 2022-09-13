#include "Player.h"
#include "Useful.h"
#include "Item.h"

Player::Player(const string& name, const string& description, Room* location, int health) :
	Creature(name, description, location, health) {}

Player::~Player(){}

void Player::Look(vector<string>& input) const
{
	parent->Look();
}

void Player::Open(vector<string>& input) const
{
	if (input.size() == 2) // Open a container (item that can be opened)
	{
		bool match = false;
		Room* room = Location();

		for (list<Entity*>::const_iterator it = room->contains.begin(); it != room->contains.end(); ++it)
		{
			if ((*it)->type == Type::ITEM)
			{
				if ((*it)->name == input[1])
				{
					Item* item = (Item*)(*it);
					match = true;

					if (!item->IsEmpty()) (*it)->Look();
					else cout << "It's empty" << endl;
				}
			}
		}
		if (!match) cout << "I can't see any " << input[1] << " in this room." << endl;
	}
}