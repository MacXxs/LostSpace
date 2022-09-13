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
	bool Action(vector<string>& input);

private:
	vector<Entity*> entities;
	Player* player;
};

#endif // !WORLD_H