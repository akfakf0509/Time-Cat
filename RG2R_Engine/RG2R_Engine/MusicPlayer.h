#pragma once
#include "Component.h"

#include <string>

#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

class MusicPlayer :
	public Component
{
private:
	IGraphBuilder* pGraph = nullptr;
	IMediaControl* pControl = nullptr;
	IBasicAudio* pBasicAudio = nullptr;

	HRESULT hr = CoInitialize(NULL);
private:
	bool isPlaying;
public:
	MusicPlayer();
	~MusicPlayer();

	virtual void Update() {};
	virtual void Render() {};
	virtual void Render(ViewRenderData&) {};

	std::type_index GetID() { return typeid(MusicPlayer); }
	static std::type_index GetFamilyID(void) { return typeid(MusicPlayer); }

	MusicPlayer* Load(const std::wstring&);
	MusicPlayer* Play();
	MusicPlayer* Pause();
	MusicPlayer* SetVolume(long);

	long GetVolume();
};
