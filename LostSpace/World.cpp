#include "World.h"
#include "Room.h"
#include "Useful.h"
#include "Item.h"
#include "Player.h"
#include "Exit.h"

World::World()
{
	/* ------------------- ROOMS ------------------- */
	Room* quarters = new Room(
		"Quarters", 
		"You are in the crew quarters. There are another 5 cryo pots, all of them empty.\n\
On the east side of the quarters you can see a window showing the emptiness of space, with \
little shinning stars in the distance."
	);
	Room* hall = new Room(
		"Main Hall", 
		"You are in the main hall. There's a big dining table in the center of the room.\n\
To the west side of the hall there's a half opened door leading to a corridor, red light \
slithers through the door openings."
	);
	Room* comms = new Room(
		"Comms Room",
		"There is a big window on the east side of the room, showing a giant planet with what \
seems 10 moons orbiting around it at the very least, the planet has an even more gygantic belt, \
formed by giant ice rocks, that disappears under the ship.\n\
On the northernmost side of the room there's a table with a bunch tool and broken communications \
equipment."
	);
	Room* bridge = new Room(
		"Glass bridge",
		"The transparent corridor that connects the Main hall of the ship with the Flight Deck.\n\
Just taking a quick look you can see that the red light that could be seen from the main hall wasn't \
light produced naturally, it's blood..., the light coming from the blue dwarf that illuminates the \
system where the spaceship is located is shining red by coming into contact with the blood splattered \
throughout the glass walls of the bridge."
	);

	entities.push_back(quarters);
	entities.push_back(hall);
	entities.push_back(comms);
	entities.push_back(bridge);

	/* ------------------- EXITS ------------------- */
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

	/* ------------------- PLAYER ------------------- */
	this->player = new Player("Isaac Cramp", "The amnesic hero of this game.", quarters, 10);

	entities.push_back(player);

	/* ------------------- ITEMS ------------------- */
	Item* backpack = new Item(
		"backpack",
		"A small backpack, it might have something inside.",
		quarters, 
		true, 
		true,
		false,
		4
	);
	Item* flashlight = new Item(
		"flashlight",
		"A small but surprisingly powerful flashlight.",
		backpack
	);
	Item* lockers = new Item(
		"lockers",
		"A bunch of lockers belonging to the crew, there might be something inside.",
		quarters,
		true,
		false,
		false,
		2
	);
	Item* key = new Item(
		"universal_key",
		"A universal_key belonging to Ben, the mechanical engineer of this crew.",
		lockers
	);
	quartersExit->key = key;

	Item* spaghetti = new Item(
		"spaghetti",
		"A bag of non-expiring spaghetti bolognese.",
		hall
	);
	Item* menstor = new Item(
		"menstor",
		"An energy drink labeled \"Menstor\", this was a banger on earth!",
		hall
	);
	Item* audiolog = new Item(
		"audiolog",
		"An audiolog left behind by someone of the crew.",
		comms
	);
	audiolog->recorder = true;
	audiolog->recording = "My name is Albert Gillingham, head of communications for the \
USG Not Ishimura, a human federation reconnaissance ship sent in search for a new habitable world.\n\
We've come into contact with some form of alien live, it entered the ship through the waste \
extraction system and it has taken a hold of Jennifer Brown, our onboard physicist. She has \
suffered a tremendous amount of mutations and is now hostile, I'm going to try and lock her up \
in the flight deck before she kills us all.\nIsaac if you find this log it will mean that \
i'm probably dead. Please try to destroy the No Ishimura, we can't allow a rescue vessel to \
take this thing back to earth.";
	Item* plasmaCutter = new Item(
		"plasma_cutter",
		"A plasma_cutter used to slice through materials quickly, it could be used as a gun",
		comms
	);

	entities.push_back(backpack);
	entities.push_back(flashlight);
	entities.push_back(lockers);
	entities.push_back(key);
	entities.push_back(spaghetti);
	entities.push_back(menstor);
	entities.push_back(audiolog);
	entities.push_back(plasmaCutter);
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
		else if (command == "use")
		{
			this->player->Use(input);
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
	default:
		valid = false;
		break;
	}
	return valid;
}