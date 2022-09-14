#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity
{
public:
	
	bool container;
	bool grabable;

	Item
	(
		const string& name, 
		const string& description, 
		Entity* location, 
		bool container = false,
		bool grabable = false
	);
	~Item();

	void Look() const;
	void Open() const;
	bool IsAContainer() const;
	bool IsEmpty() const;
	bool IsGrabable() const;
};

#endif // !ITEM_H
