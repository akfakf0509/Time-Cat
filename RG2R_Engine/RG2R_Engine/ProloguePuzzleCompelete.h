#pragma once
#include "Scene.h"
class ProloguePuzzleCompelete :
	public Scene
{
private:
	bool paused = false;

private:
	Object* puzzlePice;
	Object* puzzleCompelete;

	Object* filter;
	Object* finalText;

public:
	ProloguePuzzleCompelete();
	~ProloguePuzzleCompelete();

	void OnUpdate();
};

