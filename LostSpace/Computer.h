#ifndef COMPUTER_H
#define COMPUTER_H

#include "Item.h"

class Computer : public Item
{
public:
	Computer
	(
		const string& name,
		const string& description,
		Entity* location,
		const bool& container = false,
		const bool& grabable = true,
		const unsigned int& spaces = 0,
		bool lightSource = false
	);			  
	~Computer();
};

#endif // !COMPUTER_H