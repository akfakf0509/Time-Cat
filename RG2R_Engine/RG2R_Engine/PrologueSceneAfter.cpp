#include "stdafx.h"
#include "PrologueSceneAfter.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Effect.h"
#include "Button.h"
#include "Engine.h"

#include "ParticleSystem.h"

#include "ProloguePuzzle.h"

PrologueSceneAfter::PrologueSceneAfter() {
	cut1 = CreateObject();
	cut1->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/8.png");
	cut1->GetComponent<Transform>()
		->SetAnchor(cut1->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	cut1->AttachComponent<Effect>()
		->PushEffectInfo(new SaturationEffectInfo(0));

	cut2 = CreateObject();
	cut2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/1.png");
	cut2->GetComponent<Transform>()
		->SetAnchor(cut2->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 8.f);

	cut2_Particle = new ParticleSystem();
	cut2_Particle->GetComponent<Transform>()
		->SetPos(0, 8.f);
	cut2_Particle->PushParticlePath("Resources/Sprites/PrologueScene/After/Bloom/1.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/After/Bloom/2.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/After/Bloom/3.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/After/Bloom/4.png")
		->deleteLambda = [=](Object* obj) -> bool {
		return obj->GetComponent<Transform>()->GetPos().y < -5.5f;
	};
	cut2_Particle->moveVec = Vec2F(-1.f, -1.f);
	cut2_Particle->summonLine = Vec2F(6.f, 0);
	cut2_Particle->summon1 = 0.1f;
	cut2_Particle->summon2 = 0.3f;
	AttachObject(cut2_Particle);

	cut3 = CreateObject();
	cut3->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/2.png");
	cut3->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 16.f);

	cut4 = CreateObject();
	cut4->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/3-1.png");
	cut4->GetComponent<Transform>()
		->SetAnchor(cut4->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 16.f);

	cut5 = CreateObject();
	cut5->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/3-2.png");
	cut5->GetComponent<Transform>()
		->SetAnchor(cut5->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 16.f);
	cut5->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)));

	CommandList* commandList1 = new CommandList();

	for (float i = 0; i <= 1.1f; i += 0.1f) {
		commandList1->PushCommand([=]() {
			((ColorMatrixEffectInfo*)cut5->GetComponent<Effect>()->GetEffects()[0])->SetColor(Color(1, 1, 1, i));
		}, 0.05f);
	}
	commandList1->PushCommand([=]() {
		cameraTargetPos = Vec2F(0, 16.01f);
	}, 0);

	cut5->commandLists.push_back(commandList1);

	CommandList* commandList2 = new CommandList();

	for (float i = 1; i >= -0.1f; i -= 0.1f) {
		commandList2->PushCommand([=]() {
			((ColorMatrixEffectInfo*)cut5->GetComponent<Effect>()->GetEffects()[0])->SetColor(Color(1, 1, 1, i));
		}, 0.05f);
	}
	commandList2->PushCommand([=]() {
		cameraTargetPos = Vec2F(0, 16.f);
	}, 0);

	cut5->commandLists.push_back(commandList2);

	cut6 = CreateObject();
	cut6->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/4.png");
	cut6->GetComponent<Transform>()
		->SetAnchor(cut6->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 24.f);

	cut7 = CreateObject();
	cut7->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/5.png");
	cut7->GetComponent<Transform>()
		->SetAnchor(cut7->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 32.f);

	cut8 = CreateObject();
	cut8->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/6.png");
	cut8->GetComponent<Transform>()
		->SetAnchor(cut8->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 40.f);

	cut8_Camera = CreateObject();
	cut8_Camera->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/After/6-1.png");
	cut8_Camera->GetComponent<Transform>()
		->SetAnchor(cut8_Camera->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 38.f);

	tuto = CreateObject();
	tuto->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Helper/WheelUp.png");
	tuto->GetComponent<Transform>()
		->SetAnchor(tuto->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.5f, 0.5f);
	tuto->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1)));

	CommandList* commandList = new CommandList();
	commandList->PushCommand([]() {}, 2);
	for (float i = 1; i >= -0.1f; i -= 0.1f) {
		commandList->PushCommand([=]() {
			((ColorMatrixEffectInfo*)tuto->GetComponent<Effect>()->GetEffects()[0])->SetColor(Color(1, 1, 1, i));
		}, 0.05f);
	}

	tuto->commandLists.push_back(commandList);
	tuto->commandLists[0]->Start();

	RG2R_GameM->PauseM->resumeLambda = [=]() {
		paused = false;
		RG2R_GameM->PauseM->Reset();
	};

	AttachObject(RG2R_GameM->PauseM);
}

PrologueSceneAfter::~PrologueSceneAfter() {
}

void PrologueSceneAfter::OnUpdate() {
	if (paused) {

	}
	else {
		if (scrollDelay <= 0) {
			if (RG2R_InputM->GetMouseWheel() < 0 && cameraTargetPos.y > 0) {
				if (cameraTargetPos == Vec2F(0, 16.01f)) {
					cut5->commandLists[1]->Start();
				}
				else {
					cameraTargetPos += Vec2F(0, -8.f);
					scrollDelay = 1;
				}
			}
			else if (RG2R_InputM->GetMouseWheel() > 0 && cameraTargetPos.y < 8.f * 6) {
				if (cameraTargetPos == Vec2F(0, 16.f)) {
					cut5->commandLists[0]->Start();
				}
				else {
					cameraTargetPos += Vec2F(0, +8.f);
					scrollDelay = 1;
				}
			}
		}
		else {
			scrollDelay -= RG2R_TimeM->GetDeltaTime();
		}

		GetMainCamera()->SetPos(GetMainCamera()->GetPos() + (cameraTargetPos - GetMainCamera()->GetPos()) * RG2R_TimeM->GetDeltaTime() * 4.f);

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
			paused = true;
			RG2R_GameM->PauseM->SetIsEnable(true);
		}

		if (GetMainCamera()->GetPos().y >= 48.f) {
			RG2R_SceneM->ChangeScene(new ProloguePuzzle());
		}
	}
}