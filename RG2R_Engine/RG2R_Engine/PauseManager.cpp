#include "stdafx.h"
#include "PauseManager.h"

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
		if (GetScene()->FindObjectByName("DataManager") != nullptr) {
			GetScene()->Save();
		}

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
		if (GetScene()->FindObjectByName("DataManager") != nullptr) {
			GetScene()->Save();
		}

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