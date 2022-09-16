#include "Player.h"
#include "Useful.h"
#include "Item.h"
#include "Exit.h"
#include "Recorder.h"
#include "Computer.h"
#include "Weapon.h"
#include "Consumable.h"

Player::Player(
	const string& name, 
	const string& description, 
	const string& ripDescription,
	Room* location, 
	const int& health,
	const int& baseDamage,
	const double& armor,
	Creature* target
) :
	Creature(name, description, ripDescription, location, health, baseDamage, armor, target)
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
				else if ((*it)->type == Type::ITEM) // Look at an item
				{
					if (((Item*)(*it))->itemType == ItemType::CONSUMABLE)
					{
						((Consumable*)(*it))->Look();
					}
					else (*it)->Look();
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

		for (list<Entity*>::const_iterator it = room->contains.begin(); 
			it != room->contains.end(); ++it)
		{
			if ((*it)->type == Type::ITEM)
			{
				if ((*it)->name == input[1])
				{
					Item* item = (Item*)(*it);
					match = true;

					if (item->IsAContainer())
					{
						if (!item->IsEmpty()) (*it)->Open();
						else cout << "It's empty" << endl;
					}
					else cout << FirstLetterUpper(input[1]) << " isn't a container." << endl;

					break;
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
						else if (BackpackEquipped())
						{
							if (item->itemType == ItemType::CONSUMABLE)
							{
								if (!((Consumable*)item)->used) AddItemToBackpack(item);
								else cout << "You can't grab a consumable already consumed" << endl;
							}
							else AddItemToBackpack(item);
						}
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
	if (this->target == NULL) // Player isn't in combat
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
					else if (item->itemType == ItemType::CONSUMABLE)
					{
						cout << "To consume food use the \"consume\" command "
							<< "(first you need to grab the consumable).";
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
							<< " or it needs to be used \"on\" something." << endl;
					}
					else cout << "There is no " << input[1]
						<< " in your backpack to use." << endl;
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
	else cout << "You can't use items while being attacked. If you want to attack using \
a weapon from your inventory use the \"attack\" command." << endl;
}

void Player::Consume(const vector<string>& input)
{
	if (BackpackEquipped())
	{
		Item* item = GetItemFromBackpack(input[1]);
		if (item != NULL)
		{
			if (item->itemType == ItemType::CONSUMABLE)
			{
				((Consumable*)item)->Consume(this);
			}
			else cout << FirstLetterUpper(input[1]) << " must be a consumable" << endl;
		}
		else cout << "You don't have any " << input[1] << " in your backpack." << endl;
	}
}

void Player::Go(const vector<string>& input)
{
	if (this->target == NULL) // Player isn't in combat
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
		if (!match)
		{
			if (input[0] == "up") cout << "There's the ceiling here." << endl;
			else if (input[0] == "down") cout << "There's just floor here." << endl;
			else cout << "There's a wall here." << endl;
		}
	}
	else cout << "You can't leave while being in combat" << endl;
}

void Player::Update() 
{
	if (this->target != NULL && this->target->Dead()) this->target = NULL;
}

void Player::Attack()
{
	Creature::Attack();
}

void Player::Attack(vector<string>& input)
{
	bool match = false;

	switch (input.size())
	{
	case 1: // Attacking the enemy targeted, if any
		if (this->target != NULL) this->Attack();
		else cout << "You don't have any enemy targeted." << endl;
		break;

	case 2: // Target and attack the indicated enemy
		for (list<Entity*>::iterator it = this->parent->contains.begin();
			it != this->parent->contains.end(); it++)
		{
			if ((*it)->name == input[1])
			{
				match = true;

				if ((*it)->type == Type::CREATURE)
				{
					this->target = (Creature*)(*it);
					this->Attack();
				}
				else cout << "You can only attack creatures, and " << input[1]
					<< " is not a creature." << endl;

				break;
			}
		}
		if (!match) cout << "I can't find " << input[1] << '.' << endl;
		break;

	case 4: // Target and attack indicated enemy with gun
		for (list<Entity*>::iterator it = this->parent->contains.begin();
			it != this->parent->contains.end(); it++)
		{
			if ((*it)->name == input[1])
			{
				match = true;

				if ((*it)->type == Type::CREATURE)
				{
					this->target = (Creature*)(*it);

					if (input[2] == "with")
					{
						if (BackpackEquipped()) // Just in case
						{
							Item* item = GetItemFromBackpack(input[3]);

							if (item != NULL && item->itemType == ItemType::WEAPON)
							{
								this->AttackWithWeapon((Weapon*)item);
							}
							else cout << "You don't have a " << input[3] << '.' << endl;
						}
					}
					else cout << "You must attack someone \"with\" a weapon not \""
						<< input[2] << "\"." << endl;
				}
				else cout << "You can only attack creatures, and " << input[1] 
					<< " is not a creature." << endl;
			}
		}
		if (!match) cout << "I can't find " << input[1] << '.' << endl;
		break;

	default:
		break;
	}
}

void Player::AttackWithWeapon(Weapon* weapon)
{
	TextColor(YELLOW);
	if (!this->target->Dead() && SameRoom(this->target))
	{
		string name = this->name;
		name[0] = toupper(name[0]);

		int totalDamage = this->baseDamage + weapon->damagePoints;

		cout << "0=={==========- " << name << " attacks " << this->target->name
			<< " with a " << weapon->name << " and deals " << totalDamage 
			<< " point/s of damage." << endl;

		this->target->Attacked(totalDamage);
	}
	TextColor(GREEN);
}

void Player::Attacked(const int& damage)
{
	Creature::Attacked(damage);
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
			// If an item is a consumable i want to know the stats it provides
			if (((Item*)(*it))->itemType == ItemType::CONSUMABLE) 
			{
				((Consumable*)(*it))->Look();
			}
			else (*it)->Look();
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