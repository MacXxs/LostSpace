#include "Consumable.h"
#include "Player.h"
#include "Useful.h"

Consumable::Consumable(
	const string& name,
	const string& description,
	const string& usedDescription,
	Entity* parent,
	const int& healthRegen,
	const double& armorBoost,
	const int& boosDuration
) : Item(name, description, parent)
{
	this->itemType = ItemType::CONSUMABLE;
	this->usedDescription = usedDescription;
	this->healthRegen = healthRegen;
	this->armorBoost = armorBoost;
	this->boosDuration = boosDuration;
}

Consumable::~Consumable() {};

void Consumable::Update()
{
	if (this->armorBoost > 0 && this->used)
	{
		if (this->boosDuration > 0)
		{
			--this->boosDuration;
		}
		else if (this->boosDuration == 0)
		{
			--this->boosDuration;
			this->consumedBy->armor -= this->armorBoost;
			
			TextColor(YELLOW);
			cout << "\n0=={==========- The effects of " << this->name << " have passed."
				<< " You now negate " << consumedBy->armor << " times the incoming damage." << endl;
			TextColor(GREEN);
		}
	}
}

void Consumable::Look()
{
	if (this->used)
	{
		cout << "Consumed " << this->name << ". " << this->usedDescription << endl;
	}
	else
	{
		cout << "Some consumable " << this->name << ". " << this->description;

		if (this->healthRegen > 0)
		{
			cout << " If you consume it " << this->healthRegen
				<< " points of health will be restored." << endl;
		}
		else if (this->armorBoost > 0)
		{
			cout << " If you consume it you will negate " << this->armorBoost
				<< " times the incoming damage during " << this->boosDuration << " moves." << endl;
		}
	}
}

void Consumable::Consume(Player* player) 
{
	cout << "You've consumed the " << this->name;

	if (this->healthRegen > 0)
	{
		player->health += this->healthRegen;
		if (player->health > MAX_HEALTH)
		{
			player->health = MAX_HEALTH;
		}

		cout << " and a total of " << this->healthRegen
			<< " health points have been healed." << endl;
	}
	else if (this->armorBoost > 0)
	{
		player->armor += this->armorBoost;
		
		cout << " and you now negate " << this->armorBoost << " times the incoming damage during " 
			<< this->boosDuration << " moves." << endl;
	}
	this->used = true;

	player->contains.front()->contains.remove(this);
	player->Location()->contains.push_back(this);
	this->parent = player->Location();

	cout << FirstLetterUpper(this->name) << " dropped." << endl;

	this->consumedBy = player;
}