#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

enum class Type { ENTITY, CREATURE, EXIT, ROOM, ITEM };

class Entity
{

public:
	Type type;
	string name;
	string description;

	Entity* parent;
	list<Entity*> contains;

	Entity(const string& name, const string& description, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
};

#endif // !ENTITY_H