#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity
{
public:
	
	bool container;

	Item(const string& name, const string& description, Entity* location, bool container = false);
	~Item();

	void Look() const;
	bool IsAContainer() const;
	bool IsEmpty() const;
};

#endif // !ITEM_H
