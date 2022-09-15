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
		const int& spaces = 0,
		const string& onText = "",
		const string& offText = "",
		const string& validation = "",
		const string& error = ""
	);
	~Computer();

	void Look() const;
	void Use() const;
};

#endif // !COMPUTER_H