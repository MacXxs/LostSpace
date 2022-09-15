#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

enum class ItemType {ITEM, RECORDER, COMPUTER};

class Item : public Entity
{
public:
	
	ItemType itemType;
	bool container;
	bool grabable;
	bool lightSource;
	int spaces;
	string recording;

	Item
	(
		const string& name,
		const string& description,
		Entity* parent,
		const bool& container = false,
		const int& spaces = 0,
		const bool& grabable = true,
		const bool& lightSource = false
	);
	virtual ~Item();

	virtual void Look() const;
	virtual void Open() const;

	bool IsAContainer() const;
	bool IsEmpty() const;
	bool IsGrabable() const;
	bool IsALightSource() const;
	bool HasSpace() const;
};

#endif // !ITEM_H
