#pragma once
#include "Scene.h"

#include <vector>

class PlayingSongName;

class PrologueScene :
	public Scene
{
private:
	Vec2F cameraTargetPos = { 0, 0 };

	Object* cut1;
	Object* cut1_Background;
	Object* cut1_Cloud1;
	Object* cut1_Cloud2;
	Object* cut1_OutBackground;
	Object* cut1_Frame;
	Object* cut1_Tree;

	Object* cut2;
	Object* cut3;
	Object* cut4;
	Object* cut5;
	Object* cut6;
	Object* cut7;
	Object* cut8;

	std::vector<Object*> snows;

	Object* cut2_Frame;
	Object* cut3_Frame;
	Object* cut4_Frame;
	Object* cut5_Frame;
	Object* cut6_Frame;
	Object* cut7_Frame;
	Object* cut8_Frame;

	PlayingSongName* playingSongName;
public:
	PrologueScene();
	~PrologueScene();

	void OnUpdate();
};

