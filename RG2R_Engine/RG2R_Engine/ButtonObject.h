#pragma once
#include "UIElement.h"
class ButtonObject :
	public UIElement
{
private:
	Object* text;
public:
	ButtonObject();
	~ButtonObject();

	void OnUpdate();
};

