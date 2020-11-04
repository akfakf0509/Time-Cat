#pragma once
#include "Scene.h"

class Cat;
class PauseManager;

class SickRoom :
	public Scene
{
private:
	bool objectView = false;
	bool curtained = false;
	bool paused = false;

	Object* viewingObject;
private:
	Object* background;
	Object* shelf;
	Object* frame;
	Object* carpet;
	Object* bed;
	Object* bedOnPerson;
	Object* blanket;
	Object* curtain;
	Cat* cat;
	Object* light;
	Object* filter;
	Object* frame_EnlargeMent;
	Object* frame_EnlargeMent_Text;
	Object* bedOnPerson_Text;

	Object* dataManager;
	PauseManager* pauseManager;
public:
	SickRoom();
	~SickRoom();

	void OnUpdate();
};

