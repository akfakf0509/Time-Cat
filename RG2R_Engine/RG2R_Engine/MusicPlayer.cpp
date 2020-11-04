#include "stdafx.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
}

MusicPlayer::~MusicPlayer() {
	for (auto iter : musics) {
		iter.second->pGraph->Release();
		iter.second->pControl->Release();
		iter.second->pPosition->Release();
		iter.second->pEventEx->Release();
		iter.second->pBasicAudio->Release();
	}
	CoUninitialize();
}

void MusicPlayer::Update() {
	long eventCode, param1, param2;

	for (auto iter : musics) {
		iter.second->pEventEx->GetEvent(&eventCode, &param1, &param2, 0);

		if (eventCode == EC_COMPLETE) {
			iter.second->pPosition->put_CurrentPosition(0);
		}

		iter.second->pEventEx->FreeEventParams(eventCode, param1, param2);
	}
}

MusicPlayer* MusicPlayer::Load(const std::wstring& path) {
	auto isExist = musics.find(path);

	if (isExist == musics.end()) {
		Music* iter = new Music();

		musics.insert(std::pair<const std::wstring, Music*>(path, iter));

		currentMusic = iter;

		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&iter->pGraph);
		hr = iter->pGraph->QueryInterface(IID_IMediaControl, (void**)&iter->pControl);
		hr = iter->pGraph->QueryInterface(IID_IMediaPosition, (void**)&iter->pPosition);
		hr = iter->pGraph->QueryInterface(IID_IMediaEventEx, (void**)&iter->pEventEx);
		hr = iter->pGraph->QueryInterface(IID_IBasicAudio, (void**)&iter->pBasicAudio);

		hr = currentMusic->pGraph->RenderFile(path.c_str(), NULL);
	}
	else {
		currentMusic = (*isExist).second;
	}

	return this;
}

MusicPlayer* MusicPlayer::Play(const std::wstring& path) {
	if (currentMusic != nullptr) {
		Stop();
	}

	Load(path);

	hr = currentMusic->pControl->Run();
	
	return this;
}

MusicPlayer* MusicPlayer::Pause() {
	hr = currentMusic->pControl->Pause();

	return this;
}

MusicPlayer* MusicPlayer::Stop() {
	hr = currentMusic->pControl->Stop();
	hr = currentMusic->pPosition->put_CurrentPosition(0);

	return this;
}

MusicPlayer* MusicPlayer::SetVolume(long volume) {
	hr = currentMusic->pBasicAudio->put_Volume(volume);

	return this;
}

MusicPlayer* MusicPlayer::SetPosition(REFTIME position) {
	hr = currentMusic->pPosition->put_CurrentPosition(position);

	return this;
}

long MusicPlayer::GetVolume() {
	long volume;

	hr = currentMusic->pBasicAudio->get_Volume(&volume);

	return volume;
}

REFTIME MusicPlayer::GetPosition() {
	REFTIME position;

	currentMusic->pPosition->get_CurrentPosition(&position);

	return position;
}