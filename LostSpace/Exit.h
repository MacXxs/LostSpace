#ifndef EXIT_H
#define EXIT_H

#include "Entity.h"
#include "Item.h"
#include "Useful.h"

class Room;

class Exit : public Entity
{

public:
	Direction direction;
	Room* source;
	Room* destination;
	string openDesc;
	bool locked;
	Item* key;

	Exit
	(
		const string& name,
		const string& description,
		const string& openDesc,
		Direction direction,
		Room* source,
		Room* destination,
		bool locked
	);

	~Exit();

	void Look(const Room* room) const;
	void Unlock(const Item* item);

	bool Locked() const;
	string DoorDirection(const Room* room) const;

};

#endif // !EXIT_H