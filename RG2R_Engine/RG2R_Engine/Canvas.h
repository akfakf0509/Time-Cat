#pragma once
#include "Object.h"

#include <vector>

class Canvas :
	public Object
{
private:
	std::vector<Object*> uiElements;

	int maxSize = 0;
	int clickLimit = -1;
public:
	Canvas();
	~Canvas();

	void OnStart();
	void OnUpdate();
};

