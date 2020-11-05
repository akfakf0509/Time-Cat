#pragma once
#include "Object.h"

#include <map>
#include <string>
#include <fstream>

class DataManager
{
private:
	std::map<std::string, int> datas;

	bool loaded;
public:
	DataManager();
	~DataManager();

	DataManager* Insert(const std::string&, int);
	DataManager* Save(const std::string&);
	DataManager* Load(const std::string&);

	bool GetIsLoad();
	int GetData(const std::string&);
};

#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

struct Music
{
	IGraphBuilder* pGraph = nullptr;
	IMediaControl* pControl = nullptr;
	IMediaPosition* pPosition = nullptr;
	IMediaEventEx* pEventEx = nullptr;
	IBasicAudio* pBasicAudio = nullptr;
};

class MusicPlayer
{
private:
	HRESULT hr = CoInitialize(NULL);

private:
	std::map<const std::wstring, Music*> musics;
	Music* currentMusic = nullptr;

	bool isPlaying;

public:
	MusicPlayer();
	~MusicPlayer();

	void Update();

	MusicPlayer* Load(const std::wstring&);
	MusicPlayer* Play(const std::wstring&);
	MusicPlayer* Pause();
	MusicPlayer* Stop();
	MusicPlayer* SetVolume(long);
	MusicPlayer* SetPosition(REFTIME);

	long GetVolume();
	REFTIME GetPosition();
};

class PauseManager :
	public Object
{
private:
	Object* filter;
	Object* pauseText;
	Object* resume;
	Object* main;
	Object* exit;

public:
	std::function<void()> resumeLambda = []() {};

public:
	PauseManager();
	~PauseManager();

	void Reset();
};

class Slider;

class SettingManager :
	public Object
{
private:
	float masterVolume = 100;
	float musicVolume = 100;
	float effectVolume = 100;

private:
	Object* settingPanel;
	Slider* masterSlider;
	Slider* musicSlider;
	Slider* effectSlider;
	Object* fullscreenButton;
	Object* windowscreenButton;

public:
	std::function<void()> exitLambda = []() {};

public:
	SettingManager();
	~SettingManager();

};

#define DataM GetDataM()
#define MusicM GetMusicM()
#define PauseM GetPauseM()
#define SettingM GetSettingM()

class GameManager
{
private:
	DataManager* dataManager;
	MusicPlayer* musicManager;
	PauseManager* pauseManager;
	SettingManager* settingManager;
public:
	GameManager();
	~GameManager();

	void Update();

	DataManager* GetDataM() { return dataManager; }
	MusicPlayer* GetMusicM() { return musicManager; }
	PauseManager* GetPauseM() { return pauseManager; }
	SettingManager* GetSettingM() { return settingManager; }
};

