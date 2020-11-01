#pragma once
#include "Scene.h"
class MainScene :
	public Scene
{
private:
	Object* cat;
	Object* backgrounnd;
	Object* logo;
	Object* startText;
	Object* settingText;
	Object* exitText;
public:
	MainScene();
	~MainScene();

	void OnUpdate();
};

