#pragma once
#include "Object.h"

#include <stack>

class Canvas :
	public Object
{
private:
	std::stack<Object*> uiElements;

	int clickLimit = -1;
public:
	Canvas();
	~Canvas();

	void OnStart();
	void OnUpdate();
};

