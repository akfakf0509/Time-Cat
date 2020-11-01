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
		->SetPos(3.3f, 0.05f);

	startText = CreateObject();
	startText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Start")
		->SetTextColor(Color(0, 0, 0));
	startText->AttachComponent<BoxCollider>()
		->SetArea(3, 1);
	startText->AttachComponent<Button>();

	logo = CreateObject();
	logo->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Logo.png");
	logo->GetComponent<Transform>()
		->SetAnchor(logo->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.5f, 0.5f)
		->SetPos(-3.f, 2.f);
}

MainScene::~MainScene() {
}

void MainScene::OnUpdate() {
	//Object* object = cat;

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