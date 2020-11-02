#include "stdafx.h"
#include "MainScene.h"

#include "MusicPlayer.h"
#include "AnimationRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Transform.h"
#include "RandomGenerator.h"
#include "Engine.h"

#include "PrologueScene.h"

MainScene::MainScene() {
	musicPlayer = CreateObject()->AttachComponent<MusicPlayer>();

	musicPaths.push_back(L"Resources/Musics/Ujabes - Kafka On The Shore.mp3");
	musicPaths.push_back(L"Resources/Musics/Ujabes - Love Cells.mp3");
	musicPaths.push_back(L"Resources/Musics/Ujabes - Violet Candle.mp3");

	musicLengths.push_back(152);
	musicLengths.push_back(118);
	musicLengths.push_back(161);

	backgrounnd = CreateObject();
	backgrounnd->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Background.jpg");
	backgrounnd->GetComponent<Transform>()
		->SetAnchor(backgrounnd->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());

	cat = CreateObject();
	cat->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/MainScene")
		->SetInterval(0.1f);
	cat->GetComponent<Transform>()
		->SetAnchor(cat->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.7f, 0.7f)
		->SetPos(2.7f, 0.05f);

	startText = CreateObject();
	startText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Start")
		->SetSize(60)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	startText->AttachComponent<BoxCollider>()
		->SetArea(2.2f, 0.5f);
	startText->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::ScaleChange);
	startText->GetComponent<Transform>()
		->SetPos(-6.f, 0.4f);
	startText->onClickExit = []() { RG2R_SceneM->ChangeScene(new PrologueScene()); };

	settingText = CreateObject();
	settingText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Setting")
		->SetSize(60)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	settingText->AttachComponent<BoxCollider>()
		->SetArea(2.8f, 0.5f);
	settingText->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::ScaleChange);
	settingText->GetComponent<Transform>()
		->SetPos(-8.f, -0.2f);
	settingText->onClickExit = []() { cout << "Test" << endl; };

	exitText = CreateObject();
	exitText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Exit")
		->SetSize(60)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	exitText->AttachComponent<BoxCollider>()
		->SetArea(2.f, 0.5f);
	exitText->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::ScaleChange);
	exitText->GetComponent<Transform>()
		->SetPos(-10.f, -0.8f);
	exitText->onClickExit = []() { RG2R_WindowM->Close(); };

	logo = CreateObject();
	logo->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Logo.png");
	logo->GetComponent<Transform>()
		->SetAnchor(logo->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.5f, 0.5f)
		->SetPos(-2.8f, 2.f);
}

MainScene::~MainScene() {
}

void MainScene::OnUpdate() {
	playTime -= RG2R_TimeM->GetDeltaTime();

	if (startText->GetComponent<Transform>()->GetPos().x < -4.4f) {
		startText->GetComponent<Transform>()->Translate(6.f * RG2R_TimeM->GetDeltaTime(), 0);
	}
	else {
		startText->GetComponent<Transform>()->SetPos(-4.3f, 0.4f);
	}

	if (settingText->GetComponent<Transform>()->GetPos().x < -4.4f) {
		settingText->GetComponent<Transform>()->Translate(6.f * RG2R_TimeM->GetDeltaTime(), 0);
	}
	else {
		settingText->GetComponent<Transform>()->SetPos(-4.3f, -0.2f);
	}
	
	if (exitText->GetComponent<Transform>()->GetPos().x < -4.4f) {
		exitText->GetComponent<Transform>()->Translate(6.f * RG2R_TimeM->GetDeltaTime(), 0);
	}
	else {
		exitText->GetComponent<Transform>()->SetPos(-4.3f, -0.8f);
	}

	if (playTime < 0) {
		RandomGenerator* randomGenerator = new RandomGenerator();
		int index = randomGenerator->GetInt(0, musicPaths.size() - 1);

		musicPlayer->Load(musicPaths[index]);
		musicPlayer->Play();
		playTime = musicLengths[index];
	}

	//Object* object = startText;

	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_UP) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(0, 0.05f);
	//}
	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_DOWN) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(0, -0.05f);
	//}
	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_RIGHT) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(0.05f, 0);
	//}
	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_LEFT) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(-0.05f, 0);
	//}

	//cout << object->GetComponent<Transform>()->GetPos().x << " " << object->GetComponent<Transform>()->GetPos().y << endl;
}