#pragma once
#include "Scene.h"

class ParticleSystem;

class PrologueSceneAfter :
	public Scene
{
private:
	Vec2F cameraTargetPos = { 0, 0 };

	bool paused = false;

	float scrollDelay = 1;

private:
	Object* cut1;

	Object* cut2;
	ParticleSystem* cut2_Particle;

	Object* cut3;

	Object* cut4;

	Object* cut5;

	Object* cut6;

	Object* cut7;

	Object* cut8;
	Object* cut8_Camera;

	Object* tuto;

public:
	PrologueSceneAfter();
	~PrologueSceneAfter();

	void OnUpdate();
};

