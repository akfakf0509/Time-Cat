#pragma once
#include "Scene.h"

#include <vector>
#include <string>

class MusicPlayer;

class MainScene :
	public Scene
{
private:
	std::vector<std::wstring> musicPaths;
	std::vector<int> musicLengths;

	float playTime = 0;

	MusicPlayer* musicPlayer;

	Object* cat;
	Object* backgrounnd;
	Object* logo;
	Object* startText;
	Object* startImage;
	Object* settingText;
	Object* settingImage;
	Object* exitText;
	Object* exitImage;
public:
	MainScene();
	~MainScene();

	void OnUpdate();
};

