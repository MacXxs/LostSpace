#include "Recorder.h"
#include "Useful.h"

Recorder::Recorder
(
	const string& name,
	const string& description,
	Entity* location,
	const bool& container,
	const int& spaces,
	const bool& grabable,
	const string& recording
) : Item(name, description, location, container, spaces, grabable)
{
	this->itemType = ItemType::RECORDER;
	this->recording = recording;
}

Recorder::~Recorder() {}

void Recorder::Look() const
{
	Item::Look();
}

void Recorder::Play() const
{
	cout << "You play the " << this->name << ':' << endl;
	string recording = this->recording;

	TextColor(RED);
	TypewriterOuptut(recording);
	TextColor(GREEN);
}