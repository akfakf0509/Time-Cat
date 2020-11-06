#include "stdafx.h"
#include "GameManager.h"

DataManager::DataManager() {
	Load("Resources/Data");
}

DataManager::~DataManager() {}

DataManager* DataManager::Insert(const std::string& key, const std::string& value) {
	datas[key] = value;

	return this;
}

DataManager* DataManager::Save(const std::string& path) {
	std::ofstream writeFile;
	writeFile.open(path);

	for (auto iter : datas) {
		std::string data = iter.first + ":" + iter.second + "\n";

		writeFile.write(data.c_str(), data.size());
	}

	return this;
}

DataManager* DataManager::Load(const std::string& path) {
	std::ifstream readFile;
	readFile.open(path);

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			std::string data;

			std::getline(readFile, data);

			if (data == "") {
				break;
			}

			std::string key = data.substr(0, data.find(':'));
			std::string value = data.substr(data.find(':') + 1);

			Insert(key, value);
		}
	}
	else {
		std::cout << "Error Can't load file" << std::endl;
		std::cout << "Path : " << path << std::endl;

		Save(path);
	}

	return this;
}

bool DataManager::GetIsLoad() {
	return loaded;
}

std::string DataManager::GetData(const std::string& key) {
	if (datas.find(key) == datas.end()) {
		return "-1";
	}

	return datas[key];
}


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

	hr = currentMusic->pBasicAudio->put_Volume(volume);
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
	this->volume = volume;

	for (auto iter : musics) {
		hr = iter.second->pBasicAudio->put_Volume(volume);
	}

	return this;
}

MusicPlayer* MusicPlayer::SetPosition(REFTIME position) {
	hr = currentMusic->pPosition->put_CurrentPosition(position);

	return this;
}

long MusicPlayer::GetVolume() {
	return volume;
}

REFTIME MusicPlayer::GetPosition() {
	REFTIME position;

	currentMusic->pPosition->get_CurrentPosition(&position);

	return position;
}

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Effect.h"
#include "TextAnimation.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Engine.h"

#include "MainScene.h"

PauseManager::PauseManager() {
	GetComponent<Transform>()
		->SetIsRelative(false);
	SetIsEnable(false);

	filter = CreateChildObject();
	filter->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Filter.png");
	filter->GetComponent<Transform>()
		->SetAnchor(filter->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(1.5f, 1.5f);
	filter->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0.7f)));

	pauseText = CreateChildObject();
	pauseText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(120)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	pauseText->AttachComponent<TextAnimation>()
		->SetTargetText("Pause");
	pauseText->GetComponent<Transform>()
		->SetPos(-5.f, 1.5f);

	resume = CreateChildObject();
	resume->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(60)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	resume->AttachComponent<TextAnimation>()
		->SetTargetText("Resume")
		->SetDelay(0.2f);
	resume->GetComponent<Transform>()
		->SetPos(-4.8f, 0.5f);
	resume->AttachComponent<BoxCollider>()
		->SetArea(4.f, 0.5f);
	resume->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	resume->onClickExit = [=]() {
		SetIsEnable(false);

		resumeLambda();
	};

	main = CreateChildObject();
	main->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(60)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	main->AttachComponent<TextAnimation>()
		->SetTargetText("Main")
		->SetDelay(0.4f);
	main->GetComponent<Transform>()
		->SetPos(-4.8f, -0.1f);
	main->AttachComponent<BoxCollider>()
		->SetArea(4.f, 0.5f);
	main->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	main->onClickExit = [=]() {
		SetIsEnable(false);
		RG2R_GameM->DataM->Save("Resources/Data");
		RG2R_SceneM->ChangeScene(new MainScene());
	};

	exit = CreateChildObject();
	exit->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(60)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	exit->AttachComponent<TextAnimation>()
		->SetTargetText("Exit")
		->SetDelay(0.6f);
	exit->GetComponent<Transform>()
		->SetPos(-4.8f, -0.7f);
	exit->AttachComponent<BoxCollider>()
		->SetArea(4.f, 0.5f);
	exit->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	exit->onClickExit = [=]() {
		RG2R_GameM->DataM->Save("Resources/Data");
		RG2R_WindowM->Close();
	};
}

PauseManager::~PauseManager() {
}

void PauseManager::Reset() {
	pauseText->GetComponent<TextAnimation>()
		->Reset();

	resume->GetComponent<TextAnimation>()
		->Reset();

	main->GetComponent<TextAnimation>()
		->Reset();

	exit->GetComponent<TextAnimation>()
		->Reset();
}

#include "Slider.h"

SettingManager::SettingManager() {
	GetComponent<Transform>()
		->SetIsRelative(false);
	SetIsEnable(false);

	settingPanel = CreateChildObject();
	settingPanel->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Setting/SettingPanel.png");
	settingPanel->GetComponent<Transform>()
		->SetAnchor(settingPanel->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());

	exit = CreateChildObject();
	exit->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Setting/Exit.png");
	exit->GetComponent<Transform>()
		->SetAnchor(exit->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.35f, 0.35f)
		->SetPos(3.7f, 2.2f);
	exit->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	exit->onClickExit = [=]() {
		SetIsEnable(false);

		RG2R_GameM->DataM->Insert("masterVolume", std::to_string(masterVolume));
		RG2R_GameM->DataM->Insert("musicVolume", std::to_string(musicVolume));
		RG2R_GameM->DataM->Insert("effectVolume", std::to_string(effectVolume));
		RG2R_GameM->DataM->Insert("fullscreen", std::to_string(fullscreen));

		RG2R_GameM->DataM->Save("Resources/Data");

		exitLambda();
	};

	masterSlider = new Slider();
	masterSlider->GetComponent<Transform>()
		->SetScale(0.4f, 0.4f)
		->SetPos(2.0f, 0.95f);
	masterSlider->SetValue(masterVolume);
	masterSlider->onValueChanged = [=]() {
		masterVolume = masterSlider->GetValue();

		RG2R_GameM->DataM->Insert("masterVolume", std::to_string(masterVolume));

		RG2R_GameM->DataM->Save("Resources/Data");

		RG2R_GameM->MusicM->SetVolume(-10000 + 10000 * masterVolume * musicVolume);
	};
	settingPanel->AttachChild(masterSlider);

	musicSlider = new Slider();
	musicSlider->GetComponent<Transform>()
		->SetScale(0.4f, 0.4f)
		->SetPos(2.0f, 0.45f);
	musicSlider->SetValue(musicVolume);
	musicSlider->onValueChanged = [=]() {
		musicVolume = musicSlider->GetValue();

		RG2R_GameM->DataM->Insert("musicVolume", std::to_string(musicVolume));

		RG2R_GameM->DataM->Save("Resources/Data");

		RG2R_GameM->MusicM->SetVolume(-10000 + 10000 * masterVolume * musicVolume);
	};
	settingPanel->AttachChild(musicSlider);

	effectSlider = new Slider();
	effectSlider->GetComponent<Transform>()
		->SetScale(0.4f, 0.4f)
		->SetPos(2.0f, -0.05f);
	effectSlider->SetValue(effectVolume);
	settingPanel->AttachChild(effectSlider);

	fullscreenButton = CreateChildObject();
	fullscreenButton->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Setting/NoApply.png");
	fullscreenButton->GetComponent<Transform>()
		->SetAnchor(fullscreenButton->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.4f, 0.4f)
		->SetPos(0.7f, -0.85f);
	fullscreenButton->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_NONE);
	fullscreenButton->onClickExit = [=]() {
		fullscreen = true;

		RG2R_GameM->DataM->Insert("fullscreen", std::to_string(fullscreen));

		RG2R_GameM->DataM->Save("Resources/Data");

		RG2R_WindowM->SetFullscreen(true);

		fullscreenButton->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Setting/Apply.png");
		windowscreenButton->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Setting/NoApply.png");
	};

	windowscreenButton = CreateChildObject();
	windowscreenButton->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Setting/NoApply.png");
	windowscreenButton->GetComponent<Transform>()
		->SetAnchor(windowscreenButton->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.4f, 0.4f)
		->SetPos(0.7f, -1.35f);
	windowscreenButton->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_NONE);
	windowscreenButton->onClickExit = [=]() {
		fullscreen = false;

		RG2R_GameM->DataM->Insert("fullscreen", std::to_string(fullscreen));

		RG2R_GameM->DataM->Save("Resources/Data");

		RG2R_WindowM->SetFullscreen(false);

		fullscreenButton->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Setting/NoApply.png");
		windowscreenButton->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Setting/Apply.png");
	};
}

SettingManager::~SettingManager() {
}

void SettingManager::Load() {
	masterVolume = std::stof(RG2R_GameM->DataM->GetData("masterVolume"));
	if (masterVolume == -1) {
		masterVolume = 1;
	}
	masterSlider->SetValue(masterVolume);
	masterSlider->onValueChanged();

	musicVolume = std::stof(RG2R_GameM->DataM->GetData("musicVolume"));
	if (musicVolume == -1) {
		musicVolume = 1;
	}
	musicSlider->SetValue(musicVolume);
	musicSlider->onValueChanged();

	effectVolume = std::stof(RG2R_GameM->DataM->GetData("effectVolume"));
	if (effectVolume == -1) {
		effectVolume = 1;
	}
	effectSlider->SetValue(effectVolume);
	effectSlider->onValueChanged();

	fullscreen = std::stoi(RG2R_GameM->DataM->GetData("fullscreen"));
	if (fullscreen == -1) {
		fullscreen = 1;
	}
	RG2R_WindowM->SetFullscreen(fullscreen);

	if (fullscreen) {
		fullscreenButton->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Setting/Apply.png");
	}
	else {
		windowscreenButton->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/Setting/Apply.png");
	}
}

GameManager::GameManager() {
	dataManager = new DataManager();
	musicManager = new MusicPlayer();
	pauseManager = new PauseManager();
	settingManager = new SettingManager();
}

GameManager::~GameManager() {
	SafeDelete(dataManager);
	SafeDelete(musicManager);
	SafeDelete(pauseManager);
	SafeDelete(settingManager);
}

void GameManager::Update() {
	musicManager->Update();
}