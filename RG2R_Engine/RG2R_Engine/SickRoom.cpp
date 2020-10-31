#include "stdafx.h"
#include "SickRoom.h"

#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"
#include "Button.h"
#include "Effect.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "CollisionInfo.h"

#include "Cat.h"

SickRoom::SickRoom() {
	background = CreateObject();
	background->SetName("Background");
	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/SickRoomAllView.png");
	background->GetComponent<Transform>()
		->SetAnchor(background->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());
	background->AttachComponent<Effect>()
		->PushEffectInfo(new BlendEffectInfo(D2D1_BLEND_MODE_VIVID_LIGHT, RG2R_TextureM->Load("Resources/Sprites/SickRoomBackground/Light.png")->GetBitmap()));

	shelf = CreateObject();
	shelf->SetName("Shelf");
	shelf->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Shelf.png");
	shelf->GetComponent<Transform>()
		->SetAnchor(shelf->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-0.15f, 0.7f);
	shelf->AttachComponent<Button>();
	shelf->onClickEnter = []() {cout << "Shelf Clicked" << endl; };

	frame = CreateObject();
	frame->SetName("Frame");
	frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Frame.png");
	frame->GetComponent<Transform>()
		->SetAnchor(frame->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-0.11f, 2.15f);
	frame->AttachComponent<Button>();
	frame->onClickEnter = []() {cout << "Frame Clicked" << endl; };

	carpet = CreateObject();
	carpet->SetName("Carpet");
	carpet->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoomBackground/Carpets/Carpet.png");
	carpet->GetComponent<Transform>()
		->SetAnchor(carpet->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-6.75f, -0.85f);
	carpet->AttachComponent<Button>()
		->SetHoverTexture("Resources/Sprites/SickRoomBackground/Carpets/CarpetHover.png");
	carpet->onClickEnter = []() {cout << "Carpet Clicked" << endl; };

	//light = CreateObject();
	//light->AttachComponent<SpriteRenderer>()
	//	->SetTexture("Resources/Sprites/SickRoomBackground/Light.png");
	//light->GetComponent<Transform>()
	//	->SetAnchor(light->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
	//	->SetPos(3.2f, 0.05f);

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
		->SetAnchor(blanket->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(-5.95f, 1.4f);

	cat = AttachObject(new Cat());
}

SickRoom::~SickRoom() {}

void SickRoom::OnUpdate() {
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_STAY) {
		GetMainCamera()->Translate(-0.1f, 0);
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_STAY) {
		GetMainCamera()->Translate(0.1f, 0);
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