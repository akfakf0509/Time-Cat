#include "stdafx.h"
#include "MainScene.h"

#include "AnimationRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Transform.h"

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
		->SetScale(0.7f, 0.7f);

	startText = CreateObject();
	startText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Text");
}

MainScene::~MainScene() {
}