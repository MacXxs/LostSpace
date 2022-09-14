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

void Player::Grab(vector<string>& input)
{
	if (input.size() == 2) // Grab a grabable item
	{
		bool match = false;
		Room* room = Location();

		for (list<Entity*>::iterator it = room->contains.begin(); it != room->contains.end(); it++)
		{
			if ((*it)->type == Type::ITEM)
			{
				Item* item = (Item*)(*it);
				if (item->name == input[1])
				{
					match = true;

					if (item->IsGrabable())
					{
						if (item->name == "backpack")
						{
							Entity* parent = (Entity*)item->parent;
							parent->contains.remove(item);

							item->parent = this;
							cout << "You can now grab items and store them in your backpack!" << endl;
						}
						else if (BackpackEquipped()) AddItemToBackpack(item);
					}
					break;
				}
				else if (item->IsAContainer()) // If the item is a container I look inside
				{
					for (list<Entity*>::iterator itCont = item->contains.begin(); itCont != item->contains.end(); itCont++)
					{
						if ((*itCont)->name == input[1])
						{
							match = true;
							
							if (BackpackEquipped()) AddItemToBackpack(item);
							break;
						}
					}
				}
			}
		}
		if (!match)
		{
			cout << "I can't find any " << input[1] << "." << endl;
		}
	}
}

bool Player::BackpackEquipped() const
{
	bool equipped = this->contains.size() > 0;

	if (!equipped) cout << "You don't have any backpack to store items.";
	return equipped;
}

void Player::AddItemToBackpack(Item* item)
{
	// Change the item's parent to the backpack
	// and add the item to the list of items
	// contained in the backpack
	Entity* parent = (Entity*)item->parent;
	parent->contains.remove(item);

	Item* backpack = (Item*)this->contains.front();
	backpack->contains.push_back(item);
	item->parent = backpack;
}