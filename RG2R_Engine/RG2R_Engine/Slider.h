#pragma once
#include "Object.h"

class Slider :
	public Object
{
private:
	float value;

private:
	Object* bar;
	Object* button;

public:
	Slider();
	~Slider();

	Slider* SetValue(float);

	float GetValue();
};

