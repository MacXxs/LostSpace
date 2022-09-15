#ifndef COMPUTER_H
#define COMPUTER_H

#include "Item.h"
#include <vector>

class Exit;

class Computer : public Item
{
public:
	string onText;
	string offText;
	string validation;
	string error;
	bool done;
	Item* key;
	Exit* exit;
	bool ending;

	Computer
	(
		const string& name,
		const string& description,
		Entity* parent,
		const bool& container,
		const int& spaces,
		const bool& grabable,
		const bool& lightSource,
		const string& onText = "",
		const string& offText = "",
		const string& validation = "",
		const string& error = "",
		const bool& done = false,
		Item* key = NULL,
		Exit* exit = NULL,
		const bool& ending = false
	);
	~Computer();

	void Look() const;
	void Use();
	void Use(const Item* key);
	void Update();
};

#endif // !COMPUTER_H