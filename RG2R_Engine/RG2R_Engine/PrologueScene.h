#pragma once
#include "Scene.h"

class PlayingSongName;
class ParticleSystem;

class PrologueScene :
	public Scene
{
private:
	Vec2F cameraTargetPos = { 0, 0 };

	bool paused = false;

	float scrollDelay = 1;

private:

	Object* cut1;
	Object* cut1_Background;
	Object* cut1_Cloud1;
	Object* cut1_Cloud2;
	Object* cut1_OutBackground;
	Object* cut1_Frame;
	Object* cut1_Tree;
	Object* mouseTuto;

	Object* cut2;
	ParticleSystem* cut2_Particle;
	Object* cut2_Frame;

	Object* cut3;
	ParticleSystem* cut3_Particle;
	Object* cut3_Frame;

	Object* cut4;
	Object* cut4_Frame;

	Object* cut6;
	Object* cut6_Person;
	Object* cut6_Cat;
	Object* cut6_Frame;

	Object* cut5;
	Object* cut5_Frame;
	Object* cut5_Person;

	Object* cut7;
	Object* cut7_Frame;

	Object* cut8;
	Object* cut8_Frame;

	PlayingSongName* playingSongName;
public:
	PrologueScene();
	~PrologueScene();

	void OnUpdate();
};

