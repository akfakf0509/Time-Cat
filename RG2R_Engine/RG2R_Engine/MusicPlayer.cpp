#include "stdafx.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	hr = pGraph->QueryInterface(IID_IBasicAudio, (void**)&pBasicAudio);
}

MusicPlayer::~MusicPlayer() {
	pControl->Release();
	pGraph->Release();
	CoUninitialize();
}

MusicPlayer* MusicPlayer::Load(const std::wstring& path) {
	hr = pGraph->RenderFile(path.c_str(), NULL);

	return this;
}

MusicPlayer* MusicPlayer::Play() {
	hr = pControl->Run();
	
	return this;
}

MusicPlayer* MusicPlayer::Pause() {
	hr = pControl->Pause();

	return this;
}

MusicPlayer* MusicPlayer::SetVolume(long volume) {
	hr = pBasicAudio->put_Volume(volume);

	return this;
}

long MusicPlayer::GetVolume() {
	long volume;

	hr = pBasicAudio->get_Volume(&volume);

	return volume;
}