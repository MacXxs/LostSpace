#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity
{
public:
	
	bool container;
	bool grabable;
	bool recorder;
	int spaces;
	string recording;

	Item
	(
		const string& name,
		const string& description,
		Entity* location,
		bool container = false,
		bool grabable = true,
		bool recorder = false,
		int spaces = 0,
		const string& recording = ""
	);
	~Item();

	void Look() const;
	void Open() const;
	void Play() const;

	bool IsAContainer() const;
	bool IsEmpty() const;
	bool IsGrabable() const;
	bool IsARecorder() const;
	bool HasSapce() const;
};

#endif // !ITEM_H
