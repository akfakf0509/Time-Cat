#include "stdafx.h"
#include "PrologueScene.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"

#include "PlayingSongName.h"

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

	cut2 = CreateObject();
	cut2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/2.png");
	cut2->GetComponent<Transform>()
		->SetAnchor(cut2->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -6.f);

	cut3 = CreateObject();
	cut3->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/3.png");
	cut3->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -12.f);

	cut4 = CreateObject();
	cut4->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/4.png");
	cut4->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -18.f);

	cut5 = CreateObject();
	cut5->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/5.png");
	cut5->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -24.f);

	cut6 = CreateObject();
	cut6->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/6.png");
	cut6->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -30.f);

	cut7 = CreateObject();
	cut7->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/7.png");
	cut7->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -36.f);

	cut8 = CreateObject();
	cut8->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/8.png");
	cut8->GetComponent<Transform>()
		->SetAnchor(cut3->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -42.f);

	cut2_Frame = CreateObject();
	cut2_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut2_Frame->GetComponent<Transform>()
		->SetAnchor(cut2_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -6.f);

	cut3_Frame = CreateObject();
	cut3_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut3_Frame->GetComponent<Transform>()
		->SetAnchor(cut3_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -12.f);

	cut4_Frame = CreateObject();
	cut4_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut4_Frame->GetComponent<Transform>()
		->SetAnchor(cut4_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -18.f);

	cut5_Frame = CreateObject();
	cut5_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut5_Frame->GetComponent<Transform>()
		->SetAnchor(cut5_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -24.f);

	cut6_Frame = CreateObject();
	cut6_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut6_Frame->GetComponent<Transform>()
		->SetAnchor(cut6_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -30.f);

	cut7_Frame = CreateObject();
	cut7_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut7_Frame->GetComponent<Transform>()
		->SetAnchor(cut7_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -30.f);

	cut8_Frame = CreateObject();
	cut8_Frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/PrologueScene/Frame.png");
	cut8_Frame->GetComponent<Transform>()
		->SetAnchor(cut8_Frame->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(0, -42.f);

	playingSongName = new PlayingSongName();
	AttachObject(playingSongName);
	playingSongName->commandLists[0]->Start();
}

PrologueScene::~PrologueScene() {
}

void PrologueScene::OnUpdate() {
	if (RG2R_InputM->GetMouseWheel() < 0 && cameraTargetPos.y > -6.f * 7) {
		cameraTargetPos += Vec2F(0, -6.f);
	}
	else if (RG2R_InputM->GetMouseWheel() > 0 && cameraTargetPos.y < 0) {
		cameraTargetPos += Vec2F(0, 6.f);
	}

	GetMainCamera()->SetPos(GetMainCamera()->GetPos() + (cameraTargetPos - GetMainCamera()->GetPos()) * RG2R_TimeM->GetDeltaTime() * 6.f);

	cut1_Cloud1->GetComponent<Transform>()->Translate(-RG2R_TimeM->GetDeltaTime() * 0.1f, 0);
	cut1_Cloud2->GetComponent<Transform>()->Translate(-RG2R_TimeM->GetDeltaTime() * 0.1f, 0);

	if (cut1_Cloud1->GetComponent<Transform>()->GetPos().x <= -7.f) {
		cut1_Cloud1->GetComponent<Transform>()->SetPos(7.f, 0);
	}
	if (cut1_Cloud2->GetComponent<Transform>()->GetPos().x <= -7.f) {
		cut1_Cloud2->GetComponent<Transform>()->SetPos(7.f, 0);
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