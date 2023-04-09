#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
using namespace std;

class Entity;
class Player;

class World
{
public:
	World();
	~World();

	bool ValidCommand(vector<string>& input);
	void UpdateWorld();
	bool Action(vector<string>& input);
	void Help();

private:
	void PrintMap() const;

	vector<Entity*> entities;
	Player* player;
};

#endif // !WORLD_H