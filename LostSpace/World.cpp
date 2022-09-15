#include "World.h"
#include "Room.h"
#include "Useful.h"
#include "Item.h"
#include "Player.h"
#include "Exit.h"
#include "Recorder.h"
#include "Computer.h"
#include "Weapon.h"

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
		"You are in the main hall. There's a big dining table in the center of the room."
	);
	Room* comms = new Room(
		"Comms Room",
		"You are in the communications room. There is a big window on the east side of the room, showing a giant planet with what \
seems 10 moons orbiting around it at the very least, the planet has an even more gygantic belt, \
formed by giant ice rocks, that disappears under the ship.\n\
On the northernmost side of the room there's a table with a bunch tool and broken communications \
equipment."
	);
	Room* bridge = new Room(
		"Glass bridge",
		"You are in the glass bridge, the transparent corridor that connects the Main hall of the ship with the Flight Deck.\n\
Just taking a quick look you can see that the red light that could be seen from the main hall wasn't \
light produced naturally, it's blood..., the light coming from the blue dwarf that illuminates this \
system is shining red by coming into contact with the blood splattered throughout the glass walls of \
the bridge.\nAn id card drenched in blood can be seen on the floor, it belonged to chief engineer Reynolds."
	);
	Room* engineRoom = new Room(
		"Engine Room",
		"Once the player uses the lantern, the main source of energy for the vessel can be seen, a \
\"relatively\" small black hole wrapped around by some type of unbreakable glass. When you \
look at the black hole, the light of the flashlight curves around the glass disappearing inside it, \
leaving a circle of the darkest black you've ever seen. It's beautiful and terryfying at the \
same time.\n The room has no glass walls or windows, it's completely envolved by what seem to be the \
thickest walls on the ship.\nOn a corner of the far east of the room, there is a computer.",
		false,
		false,
		"After going down the ladder for what it seemed half a minute you touch ground. \
It's pitch black inside and you can't see nothing, the rumblings and the pulling \
forces of a strange and giant object moving on the center of the room can be heard and felt."
	);
	Room* flightDeck = new Room(
		"Flight Deck",
		"The flight deck of the ship, you can see the on-board computer to the easternmost side of \
the room next to six chairs. The wall next to the computer is made of glass, and you can see the \
rest of the system your are in, it seems it has two stars."
	);

	entities.push_back(quarters);
	entities.push_back(hall);
	entities.push_back(comms);
	entities.push_back(bridge);
	entities.push_back(engineRoom);

	/* ------------------- EXITS ------------------- */
	Exit* quartersExit = new Exit(
		"automatic_door", 
		"The door is locked shut, it seems that the emergency system is up and the ship is \
in lockdown, a universal_key will be needed to open it.", 
		"The door has been opened thanks to the universal_key.",
		Direction::WEST, 
		quarters, 
		hall, 
		true
	);
	hall->contains.push_back(quartersExit);

	Exit* hallDoor = new Exit(
		"broken_door",
		"",
		"Red light slithers through the door openings. The door is broken and can't \
close propertly, what could have done this?",
		Direction::WEST,
		hall,
		bridge,
		false
	);
	bridge->contains.push_back(hallDoor);

	Exit* hatch = new Exit(
		"hatch",
		"",
		"The hatch has a metal ladder for climbing up and down.",
		Direction::UP,
		hall,
		comms,
		false
	);
	comms->contains.push_back(hatch);

	Exit* bridgeHatch = new Exit(
		"hatch",
		"",
		"The hatch has a metal ladder for climbing up and down.",
		Direction::DOWN,
		bridge,
		engineRoom,
		false
	);
	engineRoom->contains.push_back(bridgeHatch);

	Exit* sealedDoor = new Exit(
		"security_door",
		"The security_door can only be opened once the emergency lockdown is lifted.",
		"With the lockdown lifted the door is open.",
		Direction::WEST,
		bridge,
		flightDeck,
		true
	);
	flightDeck->contains.push_back(sealedDoor);
	
	entities.push_back(quartersExit);
	entities.push_back(comms);
	entities.push_back(hallDoor);
	entities.push_back(sealedDoor);

	/* ------------------- PLAYER ------------------- */
	this->player = new Player(
		"Isaac Cramp", 
		"The unfortunate hero of this game.",
		"You are dead",
		flightDeck, 
		100,
		10,
		0.2);

	entities.push_back(player);

	/* ------------------- ENEMY ------------------- */
	Creature* alien = new Creature(
		"alien", 
		"A disfigured creature with a humanoid figure. It has long legs and arms, like a prying \
mantis, and some sort of transparent membrane covers what used to be the sides of the abdomen until \
it reaches the \"elbows\" of this aberration. The mouth has too many teeths to count, and you know \
by looking at its blank and death stare that it's going to attack at any moment.",
		"It seems to be dead but i don't know for sure, I'm not getting any closer to find \
it out.", 
		flightDeck, 
		100,
		40,
		0,
		NULL);

	entities.push_back(alien);

	/* ------------------- ITEMS ------------------- */
	Item* backpack = new Item(
		"backpack",
		"A small backpack, it might have something inside.",
		player, 
		true, 
		4,
		true,
		false
	);
	Item* flashlight = new Item(
		"flashlight",
		"A small but surprisingly powerful flashlight.",
		backpack
	);
	flashlight->lightSource = true;
	Item* lockers = new Item(
		"lockers",
		"A bunch of lockers belonging to the crew, there might be something inside.",
		quarters,
		true,
		2,
		false,
		false
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
	Item* severedHand = new Item(
		"severed_hand",
		"A very dead severed_hand.",
		bridge
	);

	entities.push_back(backpack);
	entities.push_back(flashlight);
	entities.push_back(lockers);
	entities.push_back(key);
	entities.push_back(spaghetti);
	entities.push_back(menstor);
	entities.push_back(severedHand);

	/* ------------------- WEAPONS ---------------------- */
	Weapon* plasmaCutter = new Weapon(
		"plasma_cutter",
		"A plasma_cutter used to slice through materials quickly, it could be used as a gun",
		backpack,
		15
	);

	entities.push_back(plasmaCutter);

	/* ------------------- RECORDINGS ------------------- */
	Recorder* audiolog = new Recorder(
		"audiolog",
		"An audiolog left behind by someone of the crew.",
		comms
	);
	audiolog->recording = "My name is Albert Gillingham, head of communications for the \
USG Not Ishimura, a human federation reconnaissance ship sent in search of a new habitable world.\n\
We've come into contact with some form of alien live, it entered the ship through the waste \
extraction system and it has taken a hold of Jennifer Brown, our onboard physicist. She has \
suffered a tremendous amount of mutations and is now hostile, I'm going to try and lock her up \
in the flight deck before she kills us all.\nIsaac if you find this log it will mean that \
i'm probably dead. Please try to destroy the No Ishimura, we can't allow a rescue vessel to \
take this thing back to earth.";

	entities.push_back(audiolog);

	/* ------------------- COMPUTERS ------------------- */
	Computer* securityTerminal = new Computer(
		"security_terminal",
		"A security_terminal that controls the ship's emergency system, among other things.",
		engineRoom,
		false,
		0,
		false,
		false,
		"Lockdown has been lifted. All systems running.",
		"Emergency lockdown in process, please confirm your identity \
through the handprint scanner in order to turn it off.",
		"Permission granted chief engineer Reynolds, lockdown lifted.",
		"Astronautical Engineer, Isaac Cramp. No permission to disable \
lockdown, only chief engineer Jhon Reynolds has clearance.",
		false,
		severedHand,
		sealedDoor
	);
	sealedDoor->key = securityTerminal;

	Computer* onboardComputer = new Computer(
		"onboard_computer",
		"The onboard_computer used to trace the ship routes. I could use it to trace a route \
to the closest star and kill this thing for sure.",
		flightDeck,
		false,
		0,
		false,
		false,
		"Tracing route to closest star... Brace for imminent death.",
		"",
		"",
		"Error, please try to use me directly."
);
	onboardComputer->ending = true;

	entities.push_back(securityTerminal);
	entities.push_back(onboardComputer);
}

World::~World() {}

bool World::ValidCommand(vector<string>& input)
{
	bool valid = true;

	if (input.size() > 0)
	{
		valid = Action(input);
	}
	
	UpdateWorld();

	return valid;
}

void World::UpdateWorld()
{
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		(*it)->Update();
	}
}

bool World::Action(vector<string>& input)
{
	bool valid = true;
	string command = input[0];

	if (!this->player->Dead()) {
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
			else if (command == "attack")
			{
				this->player->Attack(input);
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
			else if (command == "attack")
			{
				this->player->Attack(input);
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
			else if (command == "attack")
			{
				this->player->Attack(input);
			}
			else valid = false;
			break;
		default:
			valid = false;
			break;
		}
	}
	else cout << "You are dead, the only thing you can do is \"quit\"." << endl;

	return valid;
}