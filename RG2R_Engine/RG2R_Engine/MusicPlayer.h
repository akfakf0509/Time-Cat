#pragma once
#include "Component.h"

#include <string>
#include <map>

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

class MusicPlayer :
	public Component
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

	virtual void Update();
	virtual void Render() {};
	virtual void Render(ViewRenderData&) {};

	std::type_index GetID() { return typeid(MusicPlayer); }
	static std::type_index GetFamilyID(void) { return typeid(MusicPlayer); }

	MusicPlayer* Load(const std::wstring&);
	MusicPlayer* Play(const std::wstring&);
	MusicPlayer* Pause();
	MusicPlayer* Stop();
	MusicPlayer* SetVolume(long);
	MusicPlayer* SetPosition(REFTIME);

	long GetVolume();
	REFTIME GetPosition();
};
