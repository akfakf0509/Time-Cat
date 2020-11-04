#pragma once
#include "Object.h"

class Transform;

enum WalkDirection
{
	WALKDIRECTION_FORWARD,
	WALKDIRECTION_BACK,
	WALKDIRECTION_RIGHT,
	WALKDIRECTION_LEFT,
	WALKDIRECTION_NONE
};

class Cat :
	public Object
{
private:
	WalkDirection walkDirection = WalkDirection::WALKDIRECTION_NONE;
	WalkDirection perWalkDirection;
private:
	Object* idle;
	Object* forward;
	Object* back;
	Object* side;

	Object* ear;
	std::vector<Object*> eyes;
	std::vector<Transform*> eye_transforms;

	float ear_animation_interval = 0;
public:
	Cat();
	~Cat();

	void OnStart();
	void OnUpdate();

	void SetWalkDirection(WalkDirection);

	WalkDirection GetWalkDirection();
};

