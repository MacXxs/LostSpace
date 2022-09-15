#include "Player.h"
#include "Useful.h"
#include "Item.h"
#include "Exit.h"
#include "Recorder.h"
#include "Computer.h"

Player::Player(const string& name, const string& description, Room* location, int health) :
	Creature(name, description, location, health) 
{
	this->type = Type::PLAYER;
}

Player::~Player(){}

void Player::Look(const vector<string>& input) const
{
	bool match = false;

	if (input.size() == 1) // Look at the whole room
		this->parent->Look();
	else if (input.size() == 2)
	{
		Room* room = Location();

		for (list<Entity*>::const_iterator it = room->contains.begin();
			it != room->contains.end(); ++it)
		{
			if ((*it)->name == input[1])
			{
				match = true;

				if ((*it)->type == Type::EXIT) // Look at the exits
				{
					Exit* exit = (Exit*)(*it);
					exit->Look(room);
				}
				else (*it)->Look();
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

						if ((*it)->type == Type::ITEM) // Place item in another item
						{
							Item* container = (Item*)(*it);
							if (container->IsAContainer())
							{
								if (container->HasSpace())
								{
									Entity* backpack = item->parent;
									backpack->contains.remove(item);

									container->contains.push_back(item);
									item->parent = container;

									cout << "You've put the " << input[1] << " in the "
										<< input[3] << endl;
								}
								else
								{
									cout << "There's no room for more items in the "
										<< container->name << endl;
								}

							}
							else cout << "The destination item must be a container." << endl;
						}
						else cout << "The desintation item must be a container." << endl;
					}
				}
				if (!match) cout << "I can't find any " << input[3] << endl;
			}
			else cout << "An item has to be placed \"in\" a container, not \""
				<< input[2] << "\" a container." << endl;
		}
		else cout << "You have no " << input[1] << " in your backpack to place anywhere." << endl;
	}
}

void Player::Drop(const vector<string>& input)
{
	if (BackpackEquipped())
	{
		Item* item = GetItemFromBackpack(input[1]); // Item to be dropped

		if (item != NULL)
		{
			Entity* backpack = item->parent;
			backpack->contains.remove(item);

			Room* room = this->Location();
			room->contains.push_back(item);
			item->parent = room;

			cout << "Item dropped on the ground." << endl;
		}
		else cout << "You have no " << input[1] << " in your backpack to drop anywhere." << endl;
	}
}

void Player::Use(const vector<string>& input)
{
	
	Room* room = this->Location();
	Item* item;
	bool match = false;

	switch (input.size())
	{ 
	case 2: // Use item from backpack or item in the room

		for (list<Entity*>::iterator it = room->contains.begin();
			it != room->contains.end(); it++)
		{
			if ((*it)->name == input[1]) // Use room item
			{
				item = (Item*)(*it);
				match = true;
				if (item->itemType == ItemType::RECORDER)
				{
					Recorder* recording = (Recorder*)(item);
					recording->Play();
				}
				else if (item->itemType == ItemType::COMPUTER)
				{
					Computer* computer = (Computer*)(item);

					// You've reached the ending, and with it your death
					if (computer->ending) this->health = 0; 
					computer->Use();
				}
				else cout << "You can't use the " << input[1] << endl;
			}
		}
		if (!match)
		{
			if (BackpackEquipped())
			{
				Item* item = GetItemFromBackpack(input[1]);

				if (item != NULL) // Use backpack item
				{
					match = true;
					if (item->itemType == ItemType::RECORDER)
					{
						Recorder* recording = (Recorder*)(item);
						recording->Play();
					}
					else if (item->IsALightSource())
					{
						if (!room->Illuminated()) {
							room->lighten = true;
							cout << "You use the " << input[1] 
								<< " to illuminate the room." << endl;
							room->Look();
						}
						else cout << "The room has sufficient light to see." << endl;
					}
					else cout << "You can't use the " << input[1] 
						<< " or it need to be used \"on\" something." << endl;
				}
				else cout << "There is no " << input[1] 
					<< " in your backpack or anywhere around to use." << endl;
			}
		}

		break;
	case 4: // Use item on something
		if (BackpackEquipped())
		{
			item = GetItemFromBackpack(input[1]);

			if (item != NULL) // Use backpack item
			{
				if (input[2] == "on")
				{
					for (list<Entity*>::iterator it = room->contains.begin();
						it != room->contains.end(); it++)
					{
						if ((*it)->name == input[3])
						{
							match = true;

							if ((*it)->type == Type::EXIT) // Use item on an exit
							{
								Exit* exit = (Exit*)(*it);
								exit->Unlock(item);
							}
							else if ((*it)->type == Type::ITEM)
							{
								Item* itemAux = (Item*)(*it);
								
								if (itemAux->itemType == ItemType::COMPUTER) // Use item on a computer
								{
									Computer* computer = (Computer*)itemAux;
									computer->Use(item);
								}
								else {
									cout << "The " << input[1] << " can't be used on the "
										<< input[3] << '.' << endl;
								}
							}
							else {
								cout << "The " << input[1] << " can't be used on the "
									<< input[3] << '.' << endl;
							}
							break;
						}
					}
				}
				else cout << "An item has to be used \"on\" something else, not \""
					<< input[2] << "\" something." << endl;
			}
			else cout << "You have no " << input[1] << " in your backpack to use." << endl;
		}
		break;
	}
}

void Player::Go(const vector<string>& input)
{
	Room* room = this->Location();
	bool match = false;

	for (list<Entity*>::iterator it = room->contains.begin();
		it != room->contains.end(); it++)
	{
		if ((*it)->type == Type::EXIT) // Go through an exit
		{
			Exit* exit = (Exit*)(*it);
			
			if (input[0] == exit->DoorDirection(room))
			{
				match = true;

				if (!exit->Locked())
				{
					if (room == exit->source)
					{
						Room* destination = exit->destination;

						room->contains.remove(this);
						destination->contains.push_back(this);

						this->parent = destination;

					}
					else {
						Room* source = exit->source;

						room->contains.remove(this);
						source->contains.push_back(this);

						this->parent = source;
					}
					room->lighten = room->lightState; // Room lighting

					this->parent->Look();
				}
				else cout << "The " << exit->name << " is locked." << endl;
			}
		}
	}
	if (!match) cout << "There's a wall here." << endl;
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
	Item* backpack = (Item*)this->contains.front();

	if (backpack->HasSpace()) 
	{
		Entity* parent = (Entity*)item->parent;
		parent->contains.remove(item);

		backpack->contains.push_back(item);
		item->parent = backpack;

		cout << "You've grabbed the " << item->name << "." << endl;
	}
	else 
	{
		cout << "There's no room in your inventory for another item, drop something." << endl;
	}
}

Item* Player::GetItemFromBackpack(const string& name)
{
	Item* item = NULL;
	Item* backpack = (Item*)this->contains.front();

	for (list<Entity*>::iterator it = backpack->contains.begin();
		it != backpack->contains.end(); it++)
	{
		if ((*it)->name == name)
		{
			item = (Item*)(*it);
		}
	}
	return item;
}