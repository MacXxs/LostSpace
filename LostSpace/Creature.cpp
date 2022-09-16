#include "Creature.h"
#include "Player.h"

Creature::Creature(
	const string& name, 
	const string& description, 
	const string& ripDescription,
	Room* location, 
	const int& health,
	const int& baseDamage,
	const double& armor,
	Creature* target
) :
	Entity(name, description, location)
{
	this->type = Type::CREATURE;
	this->parent = location;
	this->health = health;
	this->baseDamage = baseDamage;
	this->armor = armor;
	this->target = target;
	this->ripDescription = ripDescription;
}

Creature::~Creature(){}

void Creature::Look() const
{
	if (!Dead())
	{
		cout << "You can see an " << name << ". " << this->description << endl;
	}
	else
	{
		cout << "You look at the " << name << "'s lifeless body. " << this->ripDescription << endl;
	}
}

void Creature::Update() 
{
	if (!Dead()) 
	{
		if (this->target != NULL)
		{
			Attack();
		}
		else
		{
			ScanForTarget();
		}
	}
}

void Creature::Attack() 
{
	cout << '\n';

	TextColor(YELLOW);
	if (!this->target->Dead() && SameRoom(this->target))
	{
		string name = this->name;
		name[0] = toupper(name[0]);

		cout << "0=={==========- " << name << " attacks " << this->target->name
			<< " and deals " << this->baseDamage << " point/s of damage." << endl;

		this->target->Attacked(this->baseDamage);
	}
	TextColor(GREEN);
}

void Creature::Attacked(const int& damage)
{
	double damageNegated = damage * this->armor;
	double totalDamage = damage - damageNegated;

	string name = this->name;
	name[0] = toupper(name[0]);

	if (this->armor != 0)
	{
		cout << "0=={==========- " << name << " negates "
			<< damageNegated << " points of incoming damge" << endl;
	}

	this->health -= totalDamage;
	if (this->health < 0) this->health = 0;

	cout << "0=={==========- " << name << " has "
		<< health << " points of health left" << endl;

	if (Dead()) cout << name << " falls dead. " << this->ripDescription << endl;
}

void Creature::ScanForTarget()
{
	bool match = false;

	for (list<Entity*>::iterator it = this->parent->contains.begin();
		it != this->parent->contains.end(); it++)
	{
		if ((*it)->type == Type::PLAYER)
		{
			match = true;

			this->target = (Player*)(*it);
			((Player*)(*it))->target = this; // The player targets the enemy targeting him
		}
	}
	if (!match) this->target = NULL;
}

bool Creature::Dead() const
{
	return health <= 0;
}

bool Creature::SameRoom(Creature* creature) const
{
	return Location() == creature->Location();
}

Room* Creature::Location() const
{
	return parent;
}