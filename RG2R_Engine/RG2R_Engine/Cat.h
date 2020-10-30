#pragma once
#include "Object.h"

class Transform;

class Cat :
	public Object
{
private:
	Object* ear;
	std::vector<Object*> eyes;
	std::vector<Transform*> eye_transforms;

	float ear_animation_interval = 0;
public:
	Cat();
	~Cat();

	void OnStart();
	void OnUpdate();
};

