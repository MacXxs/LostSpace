#include "World.h"
#include "Room.h"
#include "Useful.h"
#include "Item.h"
#include "Player.h"
#include "Exit.h"

World::World()
{
	// Rooms
	Room* quarters = new Room("Quarters", "You are in the crew quarters. \
There are another 5 cryo pots, all of them empty.\nOn the east side of the quarters \
you can see a window showing the emptiness of space, with little shinning stars in the distance.");
	Room* hall = new Room("Main Hall", "You are in the main hall. \
There's a big dining table in the center of the room.\nOn the north wall there's a ladder with a \
hatch leading to the Comms Room. To the west side of the hall there's a half opened door leading \
to a corridor, red light slithers through the door openings.");

	entities.push_back(quarters);

	// Exits
	Exit* quartersExit = new Exit("automatic door.", "The door is locked shut, it seems that \
the emergency system is up and the ship is in lockdown, a universal key will be needed to open \
it.", "The door has been opened thanks to the universal lock key.",
Direction::WEST, quarters, hall, true);

	entities.push_back(quartersExit);
	
	// Player
	player = new Player("Isaac Cramp.", "The amnesic hero of this game.", quarters, 10);

	entities.push_back(player);

	// Items
	Item* backpack = new Item("backpack", "A small backpack, it might have something inside.", quarters, true);
	Item* flashlight = new Item("flashlight", "A small but surprisingly powerful flashlight.", backpack);
	Item* lockers = new Item("lockers", "A bunch of lockers belonging to the crew, there might be \
something inside.", quarters, true);

	entities.push_back(backpack);
	entities.push_back(flashlight);
	entities.push_back(lockers);
}

World::~World(){}

bool World::ValidCommand(vector<string>& input)
{
	bool valid = true;

	if (input.size() > 0)
	{
		valid = Action(input);
	}

	return valid;
}

bool World::Action(vector<string>& input)
{
	bool valid = true;

	switch (input.size())
	{
	case 1: 
		if (input[0] == "look")
		{
			player->Look(input);
		}
		else
		{
			valid = false;
		}
		break;

	case 2:
		if (input[0] == "open")
		{
			player->Open(input);
		}
		else
		{
			valid = false;
		}
	}

	return valid;
}