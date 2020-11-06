#include "stdafx.h"
#include "PrologueScene.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Effect.h"
#include "Button.h"
#include "Engine.h"

#include "PlayingSongName.h"
#include "ParticleSystem.h"

#include "PrologueSceneAfter.h"

PrologueScene::PrologueScene() {
	cut1 = CreateObject();

	cut1_Background = new Object();
	cut1_Background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/1-Background.png");
	cut1_Background->GetComponent<Transform>()
		->SetAnchor(cut1_Background->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	cut1->AttachChild(cut1_Background);

	cut1_Cloud1 = new Object();
	cut1_Cloud1->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/1-Cloud.png");
	cut1_Cloud1->GetComponent<Transform>()
		->SetAnchor(cut1_Cloud1->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	cut1->AttachChild(cut1_Cloud1);

	cut1_Cloud2 = new Object();
	cut1_Cloud2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/1-Cloud.png");
	cut1_Cloud2->GetComponent<Transform>()
		->SetAnchor(cut1_Cloud2->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(7.f, 0);
	cut1->AttachChild(cut1_Cloud2);

	cut1_OutBackground = new Object();
	cut1_OutBackground->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/1-OutBackground.png");
	cut1_OutBackground->GetComponent<Transform>()
		->SetAnchor(cut1_OutBackground->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	cut1->AttachChild(cut1_OutBackground);

	cut1_Frame = new Object();
	cut1_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/1-Frame.png");
	cut1_Frame->GetComponent<Transform>()
		->SetAnchor(cut1_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	cut1->AttachChild(cut1_Frame);

	cut1_Tree = new Object();
	cut1_Tree->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/1-Tree.png");
	cut1_Tree->GetComponent<Transform>()
		->SetAnchor(cut1_Tree->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, 0.28f);
	cut1->AttachChild(cut1_Tree);

	mouseTuto = CreateObject();
	mouseTuto->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Helper/WheelDown.png");
	mouseTuto->GetComponent<Transform>()
		->SetAnchor(mouseTuto->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.5f, 0.5f);
	mouseTuto->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1)));

	CommandList* commandList = new CommandList();
	commandList->PushCommand([]() {}, 2);
	for (float i = 1; i >= -0.1f; i -= 0.1f) {
		commandList->PushCommand([=]() {
			((ColorMatrixEffectInfo*)mouseTuto->GetComponent<Effect>()->GetEffects()[0])->SetColor(Color(1, 1, 1, i));
		}, 0.05f);
	}

	mouseTuto->commandLists.push_back(commandList);
	mouseTuto->commandLists[0]->Start();

	cut2 = CreateObject();
	cut2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/2.png");
	cut2->GetComponent<Transform>()
		->SetAnchor(cut2->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -8.f);

	cut2_Particle = new ParticleSystem();
	cut2_Particle->GetComponent<Transform>()
		->SetPos(0, -5.f);
	cut2_Particle->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow1.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow2.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow3.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow4.png")
		->deleteLambda = [=](Object* obj) -> bool {
		return obj->GetComponent<Transform>()->GetPos().y < -5.5f;
	};
	cut2_Particle->moveVec = Vec2F(0, -1.f);
	cut2_Particle->summonLine = Vec2F(6.f, 0);
	cut2_Particle->summon1 = 0.1f;
	cut2_Particle->summon2 = 0.3f;
	AttachObject(cut2_Particle);


	cut2_Frame = CreateObject();
	cut2_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut2_Frame->GetComponent<Transform>()
		->SetAnchor(cut2_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -8.f);

	cut3 = CreateObject();
	cut3->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/3.png");
	cut3->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -16.f);

	cut3_Particle = new ParticleSystem();
	cut3_Particle->GetComponent<Transform>()
		->SetPos(0, -13.f);
	cut3_Particle->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow1.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow2.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow3.png")
		->PushParticlePath("Resources/Sprites/PrologueScene/Snow/snow4.png")
		->deleteLambda = [=](Object* obj) -> bool {
		return obj->GetComponent<Transform>()->GetPos().y < -5.5f;
	};
	cut3_Particle->moveVec = Vec2F(0, -1.f);
	cut3_Particle->summonLine = Vec2F(6.f, 0);
	cut3_Particle->summon1 = 0.1f;
	cut3_Particle->summon2 = 0.3f;
	AttachObject(cut3_Particle);

	cut3_Frame = CreateObject();
	cut3_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut3_Frame->GetComponent<Transform>()
		->SetAnchor(cut3_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -16.f);

	cut4 = CreateObject();
	cut4->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/4.png");
	cut4->GetComponent<Transform>()
		->SetAnchor(cut4->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -24.f);

	cut4_Frame = CreateObject();
	cut4_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut4_Frame->GetComponent<Transform>()
		->SetAnchor(cut4_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -24.f);

	cut6 = CreateObject();
	cut6->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/6.png");
	cut6->GetComponent<Transform>()
		->SetAnchor(cut6->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -40.f);

	cut6_Person = CreateObject();
	cut6_Person->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/6-Person.png");
	cut6_Person->GetComponent<Transform>()
		->SetAnchor(cut6_Person->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0.65f, -38.65f);

	cut6_Cat = CreateObject();
	cut6_Cat->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/6-Cat.png");
	cut6_Cat->GetComponent<Transform>()
		->SetAnchor(cut6_Cat->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -40.f);

	cut6_Frame = CreateObject();
	cut6_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut6_Frame->GetComponent<Transform>()
		->SetAnchor(cut6_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -40.f);

	cut5 = CreateObject();
	cut5->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/5.png");
	cut5->GetComponent<Transform>()
		->SetAnchor(cut5->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -32.f);

	cut5_Person = CreateObject();
	cut5_Person->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/5-Person.png");
	cut5_Person->GetComponent<Transform>()
		->SetAnchor(cut5_Person->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -32.f);

	cut5_Frame = CreateObject();
	cut5_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut5_Frame->GetComponent<Transform>()
		->SetAnchor(cut5_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -32.f);

	cut7 = CreateObject();
	cut7->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/7.png");
	cut7->GetComponent<Transform>()
		->SetAnchor(cut7->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -48.f);

	cut8 = CreateObject();
	cut8->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/8.png");
	cut8->GetComponent<Transform>()
		->SetAnchor(cut8->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -56.f);

	cut7_Frame = CreateObject();
	cut7_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut7_Frame->GetComponent<Transform>()
		->SetAnchor(cut7_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -48.f);

	cut8_Frame = CreateObject();
	cut8_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut8_Frame->GetComponent<Transform>()
		->SetAnchor(cut8_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -56.f);

	RG2R_GameM->DataM
		->Insert("Scene", std::to_string(0))
		->Save("Resources/data");

	RG2R_GameM->PauseM->resumeLambda = [=]() {
		paused = false;
		RG2R_GameM->PauseM->Reset();
	};

	AttachObject(RG2R_GameM->PauseM);

	RG2R_GameM->MusicM->Play(L"Resources/Musics/Ujabes - Violet Candle.mp3");

	playingSongName = new PlayingSongName();
	playingSongName->SetText("Ujabes - Violet Candle");
	AttachObject(playingSongName);
	playingSongName->commandLists[0]->Start();
}

PrologueScene::~PrologueScene() {
}

void PrologueScene::OnUpdate() {
	if (paused) {

	}
	else {
		if (scrollDelay <= 0) {
			if (RG2R_InputM->GetMouseWheel() < 0 && cameraTargetPos.y > -8.f * 7) {
				cameraTargetPos += Vec2F(0, -8.f);
				scrollDelay = 1;
			}
			else if (RG2R_InputM->GetMouseWheel() > 0 && cameraTargetPos.y < 0) {
				cameraTargetPos += Vec2F(0, 8.f);
				scrollDelay = 1;
			}
		}
		else {
			scrollDelay -= RG2R_TimeM->GetDeltaTime();
		}

		GetMainCamera()->SetPos(GetMainCamera()->GetPos() + (cameraTargetPos - GetMainCamera()->GetPos()) * RG2R_TimeM->GetDeltaTime() * 4.f);

		cut1_Cloud1->GetComponent<Transform>()->Translate(-RG2R_TimeM->GetDeltaTime() * 0.1f, 0);
		cut1_Cloud2->GetComponent<Transform>()->Translate(-RG2R_TimeM->GetDeltaTime() * 0.1f, 0);

		if (cut1_Cloud1->GetComponent<Transform>()->GetPos().x <= -7.f) {
			cut1_Cloud1->GetComponent<Transform>()->SetPos(7.f, 0);
		}
		if (cut1_Cloud2->GetComponent<Transform>()->GetPos().x <= -7.f) {
			cut1_Cloud2->GetComponent<Transform>()->SetPos(7.f, 0);
		}

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
			paused = true;
			RG2R_GameM->PauseM->SetIsEnable(true);
		}

		if (GetMainCamera()->GetPos().y <= -55.9f) {
			RG2R_SceneM->ChangeScene(new PrologueSceneAfter());
		}

		//Object* object = cut1_Cloud2;

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
}