#include "stdafx.h"
#include "ProloguePuzzle.h"
 
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Button.h"
#include "Engine.h"

#include "SickRoom.h"

#include "RandomGenerator.h"

ProloguePuzzle::ProloguePuzzle() {
	RandomGenerator* randomGenerator = new RandomGenerator();

	for (int i = 1; i <= 10; i++) {
		Object* tmp = CreateObject();
		tmp->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/Puzzle/Prologue/" + std::to_string(i) + ".png");
		tmp->GetComponent<Transform>()
			->SetAnchor(tmp->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
			->SetPos(randomGenerator->GetFloat(-4, 4), randomGenerator->GetFloat(-2, 2));
		tmp->AttachComponent<Button>()
			->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_NONE);
		tmp->onClickEnter = [=]() {
			Transform* transform = tmp->GetComponent<Transform>();

			mouseDistances[i - 1] = transform->GetPos() - RG2R_InputM->GetMouseWorldPos();
		};
		tmp->onClickStay = [=]() {
			Transform* transform = tmp->GetComponent<Transform>();

			transform->SetPos(RG2R_InputM->GetMouseWorldPos() + mouseDistances[i - 1]);
		};

		puzzles.push_back(tmp);
	}

	distances.push_back(Vec2F(0, 0));
	distances.push_back(Vec2F(-1.65f, -0.52f));
	distances.push_back(Vec2F(-3.01f, -0.55f));
	distances.push_back(Vec2F(-4.23f, -0.55f));
	distances.push_back(Vec2F(0.01f, 1.50f));
	distances.push_back(Vec2F(-1.39f, 0.96f));
	distances.push_back(Vec2F(-2.91f, 1.00f));
	distances.push_back(Vec2F(-4.37f, 0.95f));
	distances.push_back(Vec2F(-2.41f, 2.08f));
	distances.push_back(Vec2F(-4.26f, 2.16f));

	RG2R_GameM->DataM
		->Insert("Scene", std::to_string(1))
		->Save("Resources/data");

	RG2R_GameM->PauseM->resumeLambda = [=]() {
		paused = false;
		RG2R_GameM->PauseM->Reset();
	};

	AttachObject(RG2R_GameM->PauseM);
}

ProloguePuzzle::~ProloguePuzzle() {
}

void ProloguePuzzle::OnUpdate() {
	if (paused) {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
			RG2R_GameM->PauseM->SetIsEnable(false);
			RG2R_GameM->PauseM->resumeLambda();
		}
	}
	else {
		bool passed = true;

		for (int i = 0; i < 10; i++) {
			Vec2F point1 = puzzles[0]->GetComponent<Transform>()->GetPos();
			Vec2F point2 = puzzles[i]->GetComponent<Transform>()->GetPos();

			if ((point1 - point2 - distances[i]).Size() > 0.15f) {
				passed = false;
				break;
			}
		}

		if (passed) {
			RG2R_SceneM->ChangeScene(new SickRoom());
		}

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
			paused = true;
			RG2R_GameM->PauseM->SetIsEnable(true);
		}
	}
}