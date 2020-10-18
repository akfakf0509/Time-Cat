#pragma once
#include "Scene.h"
class SickRoom :
	public Scene
{
private:
	Object* background;
	Object* shelf;
	Object* light;
	Object* frame;
	Object* carpet;
	Object* blanket;
	Object* cat;
	Object* bed;
public:
	SickRoom();
	~SickRoom();

	void OnUpdate();
};

