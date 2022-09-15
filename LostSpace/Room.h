#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"

class Room : public Entity
{

public:
	bool lighten;
	bool lightState;
	string darkDescription;

	Room(
		const string& name,
		const string& description,
		bool lighten = true,
		bool lightState = true,
		string darkDescription = "");
	~Room();

	void Look() const;

	bool Illuminated() const;
};

#endif // !ROOM_H
