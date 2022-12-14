#ifndef RECORDER_H
#define RECORDER_H

#include "Item.h"

class Recorder : public Item
{
public:
	string recording;

	Recorder
	(
		const string& name,
		const string& description,
		Entity* location,
		const bool& container = false,
		const int& spaces = 0,
		const bool& grabable = true,
		const string& recording = ""
	);
	~Recorder();

	void Look() const;
	void Play() const;
};

#endif // !RECORDER_H
