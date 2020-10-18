#pragma once
#include <list>
#include "Scene.h"

class Enemy;
class Player;

class Ingame :
	public Scene
{
private:
	
	Object* background;
	Player* player;
	std::list<Enemy*> enemys;
public:
	Ingame();
	~Ingame();

	void OnUpdate();

	Ingame* SpawnEnemy();
};