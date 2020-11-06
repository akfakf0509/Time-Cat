#pragma once
#include "Scene.h"
class BeforeStart :
	public Scene
{
private:
	Object* filter;
	Object* headSet;
	Object* text;
public:
	BeforeStart();
	~BeforeStart();

	void OnStart();
};

