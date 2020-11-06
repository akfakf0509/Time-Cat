#include "stdafx.h"
#include "ProloguePuzzleCompelete.h"

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "TextAnimation.h"
#include "Transform.h"
#include "Effect.h"
#include "Button.h"
#include "Engine.h"

#include "MainScene.h"

ProloguePuzzleCompelete::ProloguePuzzleCompelete() {
	puzzlePice = CreateObject();
	puzzlePice->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Puzzle/Prologue/6-1.png");
	puzzlePice->GetComponent<Transform>()
		->SetAnchor(puzzlePice->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	puzzlePice->AttachComponent<Button>();
	puzzlePice->onClickEnter = [=]() {
		puzzleCompelete->SetIsEnable(true);
		puzzleCompelete->commandLists[0]->Start();
		puzzlePice->SetIsEnable(false);
	};

	puzzleCompelete = CreateObject();
	puzzleCompelete->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Puzzle/Prologue/Compelete.png");
	puzzleCompelete->GetComponent<Transform>()
		->SetAnchor(puzzleCompelete->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	puzzleCompelete->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)));
	puzzleCompelete->SetIsEnable(false);

	CommandList* commandList = new CommandList();
	for (float i = 0; i <= 1.1f; i += 0.01f) {
		commandList->PushCommand([=]() {
			((ColorMatrixEffectInfo*)puzzleCompelete->GetComponent<Effect>()->GetEffects()[0])->SetColor(Color(1, 1, 1, i));
		}, 0.05f);
	}
	commandList->PushCommand([=]() {
		filter->SetIsEnable(true);
		finalText->SetIsEnable(true);
	}, 3);

	commandList->PushCommand([=]() {
		finalText->GetComponent<TextAnimation>()->Reset();
		finalText->GetComponent<TextAnimation>()->SetTargetText("���������� �з��� ���� �����ϴ�! \n\n�÷��� ���ּż� �����մϴ�! ���� ���� ������ �ϰԵȴٸ� ���丮�� ������ ������ּ���!");
	}, 8);

	commandList->PushCommand([=]() {
		RG2R_GameM->DataM->Insert("Scene", "0");
		RG2R_GameM->DataM->Save("Resources/Data");
		RG2R_SceneM->ChangeScene(new MainScene());
	}, 10);

	puzzleCompelete->commandLists.push_back(commandList);

	filter = CreateObject();
	filter->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Filter.png");
	filter->GetComponent<Transform>()
		->SetAnchor(filter->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(1.5f, 1.5f)
		->SetIsRelative(false);
	filter->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0.7f)));
	filter->SetIsEnable(false);

	finalText = CreateObject();
	finalText->GetComponent<Transform>()
		->SetIsRelative(false);
	finalText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll �ʷϿ����")
		->SetSize(30)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
	finalText->AttachComponent<TextAnimation>()
		->SetTargetText("������ �ϼ����� ����̴� ���ڱ� ���� ������ �Ʒ��´�..");
	finalText->SetIsEnable(false);

	RG2R_GameM->DataM
		->Insert("Scene", std::to_string(3))
		->Save("Resources/data");

	RG2R_GameM->PauseM->resumeLambda = [=]() {
		paused = false;
		RG2R_GameM->PauseM->Reset();
	};

	AttachObject(RG2R_GameM->PauseM);
}

ProloguePuzzleCompelete::~ProloguePuzzleCompelete() {
}

void ProloguePuzzleCompelete::OnUpdate() {
	if (paused) {

	}
	else {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
			paused = true;
			RG2R_GameM->PauseM->SetIsEnable(true);
		}
	}
}