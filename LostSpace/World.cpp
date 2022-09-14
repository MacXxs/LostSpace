#include "World.h"
#include "Room.h"
#include "Useful.h"
#include "Item.h"
#include "Player.h"
#include "Exit.h"

World::World()
{
	// Rooms
	Room* quarters = new Room(
		"Quarters", 
		"You are in the crew quarters. There are another 5 cryo pots, all of them empty.\n\
On the east side of the quarters you can see a window showing the emptiness of space, with \
little shinning stars in the distance.");
	Room* hall = new Room(
		"Main Hall", 
		"You are in the main hall. There's a big dining table in the center of the room.\n\
To the west side of the hall there's a half opened door leading to a corridor, red light \
slithers through the door openings.");
	Room* comms = new Room(
		"Comms Room",
		"There is a big window on the east side of the room, showing a giant planet with what \
seems 10 moons orbiting around it at the very least, the planet has an even more gygantic belt \
formed by giant rocks of ice that disappear under the ship.");

	entities.push_back(quarters);
	entities.push_back(hall);
	entities.push_back(comms);

	// Exits
	Exit* quartersExit = new Exit(
		"automatic_door", 
		"The door is locked shut, it seems that the emergency system is up and the ship is \
in lockdown, a universal_key will be needed to open it.", 
		"The door has been opened thanks to the universal_key.",
		Direction::WEST, 
		quarters, 
		hall, 
		true);
	hall->contains.push_back(quartersExit);

	Exit* hatch = new Exit(
		"hatch",
		"",
		"The hatch has a metal ladder for climbing up and down.",
		Direction::UP,
		hall,
		comms,
		false);
	comms->contains.push_back(hatch);
	
	entities.push_back(quartersExit);
	entities.push_back(comms);

	// Player
	this->player = new Player("Isaac Cramp", "The amnesic hero of this game.", quarters, 10);

	entities.push_back(player);

	// Items
	Item* backpack = new Item(
		"backpack",
		"A small backpack, it might have something inside.",
		quarters, true, true);
	Item* flashlight = new Item(
		"flashlight",
		"A small but surprisingly powerful flashlight.",
		backpack,
		false,
		true);
	Item* lockers = new Item(
		"lockers",
		"A bunch of lockers belonging to the crew, there might be something inside.",
		quarters,
		true,
		false);
	Item* key = new Item(
		"universal_key",
		"A universal_key belonging to Ben, the mechanical engineer of this crew.",
		lockers,
		false,
		true);
	quartersExit->key = key;

	Item* spaghetti = new Item(
		"spaghetti",
		"A bag of non-spoiling spaghetti bolognese.",
		hall,
		false,
		true
	);
	Item* menstor = new Item(
		"menstor",
		"An energy drink labeled \"Menstor\", this was a banger on earth!",
		hall,
		false,
		true
	);

	entities.push_back(backpack);
	entities.push_back(flashlight);
	entities.push_back(lockers);
	entities.push_back(key);
	entities.push_back(spaghetti);
	entities.push_back(menstor);
}

World::~World() {}

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
	string command = input[0];

	switch (input.size())
	{
	case 1:
		if (command == "look")
		{
			this->player->Look(input);
		}
		else if (command == "inventory")
		{
			this->player->Inventory();
		}
		else if (command == "north" || command == "south" || command == "east" ||
			command == "west" || command == "up" || command == "down") 
		{
			this->player->Go(input);
		}
		else valid = false;
		break;

	case 2:
		if (command == "look")
		{
			this->player->Look(input);
		}
		else if (command == "open")
		{
			this->player->Open(input);
		}
		else if (command == "grab")
		{
			this->player->Grab(input);
		}
		else if (command == "drop")
		{
			this->player->Drop(input);
		}
		else valid = false;
		break;

	case 4:
		if (command == "place")
		{
			this->player->Place(input);
		}
		else if (command == "use")
		{
			this->player->Use(input);
		}
		else valid = false;
		break;
	}
	return valid;
}