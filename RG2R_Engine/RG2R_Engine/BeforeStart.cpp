#include "stdafx.h"
#include "BeforeStart.h"

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Transform.h"
#include "TextAnimation.h"
#include "Effect.h"
#include "Engine.h"

#include "MainScene.h"

BeforeStart::BeforeStart() {
	filter = CreateObject();
	filter->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Filter.png");
	filter->GetComponent<Transform>()
		->SetAnchor(filter->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(1.5f, 1.5f);
	filter->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1.f)));

	headSet = filter->CreateChildObject();
	headSet->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/HeadSet.png");
	headSet->GetComponent<Transform>()
		->SetAnchor(headSet->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.5f, 0.5f);

	text = filter->CreateChildObject();
	text->GetComponent<Transform>()
		->SetPos(0, -1.f);
	text->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(30)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
	text->AttachComponent<TextAnimation>()
		->SetTargetText("헤드셋을 착용하시면 더 몰입감있게 게임을 플레이 하실 수 있습니다.")
		->SetInterval(0.02f);

	CommandList* commandList = new CommandList();

	commandList->PushCommand([=]() {
		headSet->SetIsEnable(false);
		text->GetComponent<TextAnimation>()->Reset();
		text->GetComponent<TextAnimation>()->SetTargetText("고양이가 숨는걸 좋아하는 이유를 아시나요?");
	}, 3);

	commandList->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new MainScene());
	}, 1.5f);

	filter->commandLists.push_back(commandList);
	filter->commandLists[0]->Start();
}

BeforeStart::~BeforeStart() {
}

void BeforeStart::OnStart() {
	RG2R_GameM->SettingM->Load();
}