#include "Player.h"
#include "Useful.h"
#include "Item.h"

Player::Player(const string& name, const string& description, Room* location, int health) :
	Creature(name, description, location, health) 
{
	this->type = Type::PLAYER;
}

Player::~Player(){}

void Player::Look(const vector<string>& input) const
{
	bool match = false;

	if (input.size() == 1) // Look at the room
		parent->Look();
	else if (input.size() == 2)
	{
		Room* room = Location();

		for (list<Entity*>::const_iterator it = room->contains.begin();
			it != room->contains.end(); ++it)
		{
			if ((*it)->name == input[1])
			{
				match = true;

				(*it)->Look();
				break;
			}
		}
		if (!match) cout << "I see no " << input[1] << " in this room." << endl;
	}

}

void Player::Open(const vector<string>& input) const
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

					if (!item->IsEmpty()) (*it)->Open();
					else cout << "It's empty" << endl;
				}
			}
		}
		if (!match) cout << "I can't see any " << input[1] << " in this room." << endl;
	}
}

void Player::Grab(const vector<string>& input)
{
	if (input.size() == 2) // Grab a grabable item
	{
		bool match = false;
		Room* room = Location();

		for (list<Entity*>::iterator it = room->contains.begin(); 
			it != room->contains.end(); it++)
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
							this->contains.push_back(item);

							cout << "You can now grab items and store them in your backpack!" << endl;
						}
						else if (BackpackEquipped()) AddItemToBackpack(item);
					}
					break;
				}
				else if (item->IsAContainer()) // If the item is a container I look inside
				{
					for (list<Entity*>::iterator itCont = item->contains.begin(); 
						itCont != item->contains.end(); itCont++)
					{
						if ((*itCont)->name == input[1])
						{
							Item* itemInContainer = (Item*)(*itCont);
							match = true;
							
							if (BackpackEquipped()) AddItemToBackpack(itemInContainer);
							break;
						}
					}
					if (match) break;
				}
			}
		}
		if (!match)
		{
			cout << "I can't find any " << input[1] << "." << endl;
		}
	}
}

void Player::Place(const vector<string>& input)
{
	if (BackpackEquipped())
	{
		Item* item = GetItemFromBackpack(input[1]); // Item to be placed

		if (item != NULL)
		{
			Room* room = this->Location();
			bool match = false;

			if (input[2] == "in")
			{
				for (list<Entity*>::iterator it = room->contains.begin();
					it != room->contains.end(); it++)
				{
					if ((*it)->name == input[3])
					{
						match = true;

						if ((*it)->type == Type::ITEM)
						{
							Item* container = (Item*)(*it);
							if (container->IsAContainer())
							{
								Entity* parent = item->parent;
								parent->contains.remove(item);

								container->contains.push_back(item);
								item->parent = container;

								cout << "You've put the " << input[1] << " in the " << input[3] << endl;
							}
							else cout << "The destination item must be a container." << endl;
						}
						else cout << "The desintation item must be a container." << endl;
					}
				}
				if (!match) cout << "I can't find any " << input[3] << endl;
			}
			else cout << "An item has to be placed \"in\" a container, not \"" << input[2] << "\"." << endl;
		}
	}
}

void Player::Inventory() const
{
	if (BackpackEquipped())
	{
		Item* backpack = (Item*)this->contains.front();

		cout << "You look inside your backpack and you find: " << endl;
		for (list<Entity*>::iterator it = backpack->contains.begin();
			it != backpack->contains.end(); it++)
		{
			cout << "\t- ";
			(*it)->Look();
		}
	}
}

bool Player::BackpackEquipped() const
{
	bool equipped = this->contains.size() > 0;
	
	if (!equipped) cout << "You don't have a backpack to take from or store items." << endl;
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

	cout << "You've grabbed the " << item->name << "." << endl;
}

Item* Player::GetItemFromBackpack(const string& name)
{
	Item* item = NULL;
	Item* backpack = (Item*)this->contains.front();
	bool match = false;

	for (list<Entity*>::iterator it = backpack->contains.begin();
		it != backpack->contains.end(); it++)
	{
		if ((*it)->name == name)
		{
			item = (Item*)(*it);
			match = true;
		}
	}

	if (!match) cout << "You have no " << name << " in your backpack." << endl;
	return item;
}