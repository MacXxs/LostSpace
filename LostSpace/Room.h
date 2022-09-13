#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"

class Room : public Entity
{
public:
	Room(const string& name, const string& description);
	~Room();

	void Look() const;
};

#endif // !ROOM_H
