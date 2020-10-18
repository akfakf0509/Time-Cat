#include "stdafx.h"
#include "SickRoom.h"

#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"
#include "Button.h"

SickRoom::SickRoom() {
	background = CreateObject();
	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/SickRoomAllView.png");
	background->GetComponent<Transform>()
		->SetAnchor(background->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());

	shelf = CreateObject();
	shelf->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Shelf.png");
	shelf->GetComponent<Transform>()
		->SetAnchor(shelf->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-0.15f, 0.7f);
	shelf->AttachComponent<Button>();
	shelf->onClickEnter = []() {cout << "Shelf Clicked" << endl; };

	frame = CreateObject();
	frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Frame.png");
	frame->GetComponent<Transform>()
		->SetAnchor(frame->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-0.11f, 2.15f);
	frame->AttachComponent<Button>();
	frame->onClickEnter = []() {cout << "Frame Clicked" << endl; };
	
	carpet = CreateObject();
	carpet->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Carpet.png");
	carpet->GetComponent<Transform>()
		->SetAnchor(carpet->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-6.75f, -0.8f);
	carpet->AttachComponent<Button>();
	carpet->onClickEnter = []() {cout << "Carpet Clicked" << endl; };


	light = CreateObject();
	light->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Light.png");
	light->GetComponent<Transform>()
		->SetAnchor(light->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(3.2f, 0.05f);

	bed = CreateObject();
	bed->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Bed.png");
	bed->GetComponent<Transform>()
		->SetAnchor(bed->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-6.45f, 0.9f);

	blanket = CreateObject();
	blanket->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/SickRoomBackground/BlanketAnimation");
	blanket->GetComponent<Transform>()
		->SetAnchor(blanket->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-7.05f, 0.3f);

	cat = CreateObject();
	cat->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/EarAnimation")
		->PushTextures("Resources/Sprites/CatAnimations/TailAnimation")
		->SetTargetAnim(0)
		->SetInterval(0.1f)
		->SetIsLoop(false);
}

SickRoom::~SickRoom() {}

void SickRoom::OnUpdate() {
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_STAY) {
		GetMainCamera()->Translate(-0.1f, 0);
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_STAY) {
		GetMainCamera()->Translate(0.1f, 0);
	}

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_P) == KeyState::KEYSTATE_STAY) {
		cat->GetComponent<AnimationRenderer>()->Play();
	}

	//Object* object = blanket;

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