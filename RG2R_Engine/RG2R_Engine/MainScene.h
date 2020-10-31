#pragma once
#include "Scene.h"
class MainScene :
	public Scene
{
private:
	Object* cat;
	Object* backgrounnd;
	Object* startText;
public:
	MainScene();
	~MainScene();
};

