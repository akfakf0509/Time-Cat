#pragma once
#include "UIElement.h"

class Slider :
	public UIElement
{
private:
	float perValue;
	float value;

private:
	Object* bar;
	Object* button;

public:
	std::function<void()> onValueChanged = []() {};

public:
	Slider();
	~Slider();

	void OnUpdate();

	Slider* SetValue(float);

	float GetValue();
};

