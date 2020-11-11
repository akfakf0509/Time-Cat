#pragma once
#include "Scene.h"

#include <vector>
class ProloguePuzzle :
	public Scene
{
private:
	std::vector<Vec2F> mouseDistances = std::vector<Vec2F>(10);
	std::vector<Vec2F> distances;

	bool paused = false;

private:
	std::vector<Object*> puzzles;

public:
	ProloguePuzzle();
	~ProloguePuzzle();

	void OnRenderBefore();
	void OnUpdate();
};

