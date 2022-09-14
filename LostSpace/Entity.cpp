#include "Entity.h"

Entity::Entity(const string& name, const string& description, Entity* parent = NULL)
{
	this->type = Type::ENTITY;
	this->name = name;
	this->description = description;
	this->parent = parent;

	if (parent != NULL) parent->contains.push_back(this);
}

Entity::~Entity(){}

void Entity::Look() const
{
	cout << name << endl;
	cout << description << endl;
}

