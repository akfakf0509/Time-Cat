#pragma once
#include "Object.h"
class UIElement :
	public Object
{
public:
	bool clickedOn = false;

public:
	UIElement();
	~UIElement();
};

