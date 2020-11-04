#pragma once
#include "Object.h"
class PauseManager :
	public Object
{
private:
	Object* filter;
	Object* pauseText;
	Object* resume;
	Object* main;
	Object* exit;

public:
	std::function<void()> resumeLambda = []() {};

public:
	PauseManager();
	~PauseManager();

	void Reset();
};

