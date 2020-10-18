#pragma once
#include "Object.h"

class Enemy :
	public Object
{
private:
	int hp;

	Object* target;
public:
	Enemy();
	~Enemy();

	void OnUpdate();
	void OnCollisionStay(CollisionInfo*);

	int GetHp();

	Enemy* SetTarget(Object*);
	Enemy* SetHp(int);
};

