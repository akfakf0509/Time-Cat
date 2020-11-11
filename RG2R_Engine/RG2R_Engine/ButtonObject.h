#pragma once
#include "Object.h"
class ButtonObject :
	public Object
{
private:
	Object* text;
public:
	ButtonObject();
	~ButtonObject();
};

