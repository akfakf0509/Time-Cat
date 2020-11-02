#pragma once
#include "Scene.h"
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
public:
	PrologueScene();
	~PrologueScene();

	void OnUpdate();
};

