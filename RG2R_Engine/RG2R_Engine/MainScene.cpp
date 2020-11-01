#include "stdafx.h"
#include "MainScene.h"

#include "AnimationRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Transform.h"
#include "Engine.h"

MainScene::MainScene() {
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
	startText->onClickExit = []() { cout << "Test" << endl; };

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
	exitText->onClickExit = []() { cout << "Test" << endl; };

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
	if (startText->GetComponent<Transform>()->GetPos().x < -4.3f) {
		startText->GetComponent<Transform>()->Translate(0.05f, 0);
	}

	if (settingText->GetComponent<Transform>()->GetPos().x < -4.3f) {
		settingText->GetComponent<Transform>()->Translate(0.05f, 0);
	}
	
	if (exitText->GetComponent<Transform>()->GetPos().x < -4.3f) {
		exitText->GetComponent<Transform>()->Translate(0.05f, 0);
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