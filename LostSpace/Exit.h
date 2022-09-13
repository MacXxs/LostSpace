#ifndef EXIT_H
#define EXIT_H

#include "Entity.h"

enum class Direction { NORTH, SOUTH, EAST, WEST, UP, DOWN};

class Room;

class Exit : public Entity
{

public:
	Direction direction;
	Room* source;
	Room* destination;

	string openDesc;
	bool locked;

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

	void Look() const;
	bool Locked() const;
	string DoorDirection() const;

};

#endif // !EXIT_H