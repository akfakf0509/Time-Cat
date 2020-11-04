#pragma once
#include "Scene.h"

#include <vector>
#include <string>

class MusicPlayer;
class PlayingSongName;

class MainScene :
	public Scene
{
private:
	Vec2F perMousePos;

	std::vector<std::string> musicPaths;
	std::vector<int> musicLengths;

	float playTime = 0;
private:
	MusicPlayer* musicPlayer;
	PlayingSongName* playingSongName;

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

