#include "stdafx.h"
#include "SickRoom.h"

#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"
#include "TextRenderer.h"
#include "TextAnimation.h"
#include "Button.h"
#include "Effect.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "CollisionInfo.h"

#include "Cat.h"
#include "PlayingSongName.h"

#include "ProloguePuzzleCompelete.h"

SickRoom::SickRoom() {
	background = CreateObject();
	background->SetName("Background");
	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/SickRoomLight.png");
	background->GetComponent<Transform>()
		->SetAnchor(background->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());

	shelf = CreateObject();
	shelf->SetName("Shelf");
	shelf->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Shelf.png");
	shelf->GetComponent<Transform>()
		->SetAnchor(shelf->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-0.15f, 0.7f);
	shelf->AttachComponent<Button>();
	shelf->onClickEnter = [=]() {
		if (sickRoomKey) {
			RG2R_SceneM->ChangeScene(new ProloguePuzzleCompelete());
		}

		objectView = true;
		viewingObject = shelf_Text;
		filter->SetIsEnable(true);
		viewingObject->SetIsEnable(true);
	};

	frame = CreateObject();
	frame->SetName("Frame");
	frame->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Frame.png");
	frame->GetComponent<Transform>()
		->SetAnchor(frame->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-0.11f, 2.15f);
	frame->AttachComponent<Button>();
	frame->onClickEnter = [=]() {
		objectView = true;
		viewingObject = frame_EnlargeMent;
		filter->SetIsEnable(true);
		frame_EnlargeMent->SetIsEnable(true);
	};

	carpet = CreateObject();
	carpet->SetName("Carpet");
	carpet->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Carpets/Carpet.png");
	carpet->GetComponent<Transform>()
		->SetAnchor(carpet->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-6.75f, -0.85f);
	carpet->AttachComponent<Button>()
		->SetHoverTexture("Resources/Sprites/SickRoom/Carpets/CarpetHover.png")
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_IMAGECHANGE);
	carpet->onClickEnter = [=]() {
		if (!sickRoomKey) {
			sickRoomKey = true;
		}
		else {
			key_EnlargeMent->GetComponent<SpriteRenderer>()->SetIsEnable(false);
			key_EnlargeMent_Text->GetComponent<TextAnimation>()->Reset();
			key_EnlargeMent_Text->GetComponent<TextAnimation>()->SetTargetText("열쇠를 얻은 곳이다..");
		}

		objectView = true;
		viewingObject = key_EnlargeMent;
		filter->SetIsEnable(true);
		viewingObject->SetIsEnable(true);
	};

	bed = CreateObject();
	bed->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Bed.png");
	bed->GetComponent<Transform>()
		->SetAnchor(bed->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter())
		->SetPos(-6.45f, 0.9f);

	bedOnPerson = CreateObject();
	bedOnPerson->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/BedOnPerson.png");
	bedOnPerson->GetComponent<Transform>()
		->SetAnchor(bedOnPerson->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(-7.9f, 2.f)
		->SetScale(0.4f, 0.4f);
	bedOnPerson->AttachComponent<Button>();
	bedOnPerson->onClickEnter = [=]() {
		objectView = true;
		viewingObject = bedOnPerson_Text;
		filter->SetIsEnable(true);
		viewingObject->SetIsEnable(true);
	};

	blanket = CreateObject();
	blanket->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/SickRoom/BlanketAnimation");
	blanket->GetComponent<Transform>()
		->SetAnchor(blanket->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(-6.f, 1.5f);

	curtain = CreateObject();
	curtain->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/CurtainOpen.png");
	curtain->GetComponent<Transform>()
		->SetAnchor(curtain->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetPos(4.05f, 2.18f);
	curtain->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_NONE);
	curtain->onClickEnter = [=]() {
		if (curtained) {
			curtained = !curtained;
			curtain->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/SickRoom/CurtainOpen.png");
			background->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/SickRoom/SickRoomLight.png");
			light->SetIsEnable(true);
		}
		else {
			curtained = !curtained;
			curtain->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/SickRoom/CurtainClosed.png");
			background->GetComponent<SpriteRenderer>()->SetTexture("Resources/Sprites/SickRoom/SickRoomNoLight.png");
			light->SetIsEnable(false);
		}
	};

	cat = new Cat();
	AttachObject(cat);

	light = CreateObject();
	light->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/Light.png");
	light->GetComponent<Transform>()
		->SetAnchor(light->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());

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

	frame_EnlargeMent = CreateObject();
	frame_EnlargeMent->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/EnlargedObject/Frame.png");
	frame_EnlargeMent->GetComponent<Transform>()
		->SetAnchor(frame_EnlargeMent->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetIsRelative(false);
	frame_EnlargeMent->SetIsEnable(false);

	frame_EnlargeMent_Text = new Object();
	frame_EnlargeMent_Text->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(30)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
	frame_EnlargeMent_Text->AttachComponent<TextAnimation>()
		->SetTargetText("이유는 모르겠지만 그리운 느낌이다..");
	frame_EnlargeMent_Text->GetComponent<Transform>()
		->SetPos(0, -2.5f);
	frame_EnlargeMent->AttachChild(frame_EnlargeMent_Text);

	bedOnPerson_Text = CreateObject();
	bedOnPerson_Text->GetComponent<Transform>()
		->SetIsRelative(false);
	bedOnPerson_Text->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(30)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
	bedOnPerson_Text->AttachComponent<TextAnimation>()
		->SetTargetText("날 거둬준 집사다.. 어딘가 괴로워 보인다...");
	bedOnPerson_Text->SetIsEnable(false);

	key_EnlargeMent = CreateObject();
	key_EnlargeMent->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SickRoom/EnlargedObject/Key.png");
	key_EnlargeMent->GetComponent<Transform>()
		->SetAnchor(key_EnlargeMent->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetIsRelative(false);
	key_EnlargeMent->SetIsEnable(false);

	key_EnlargeMent_Text = key_EnlargeMent->CreateChildObject();
	key_EnlargeMent_Text->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(30)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
	key_EnlargeMent_Text->AttachComponent<TextAnimation>()
		->SetTargetText("열쇠다.. 어디에 쓰이는 열쇠일까?");
	key_EnlargeMent_Text->GetComponent<Transform>()
		->SetPos(0, -2.5f);

	shelf_Text = CreateObject();
	shelf_Text->GetComponent<Transform>()
		->SetIsRelative(false);
	shelf_Text->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetSize(30)
		->SetTextColor(Color(1, 1, 1))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
	shelf_Text->AttachComponent<TextAnimation>()
		->SetTargetText("잠겨있다..");
	shelf_Text->SetIsEnable(false);

	tuto = CreateObject();
	tuto->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Helper/MoveKey.png");
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

	RG2R_GameM->DataM
		->Insert("Scene", std::to_string(2))
		->Save("Resources/data");

	RG2R_GameM->PauseM->resumeLambda = [=]() {
		paused = false;
		RG2R_GameM->PauseM->Reset();
	};

	AttachObject(RG2R_GameM->PauseM);

	RG2R_GameM->MusicM->Play(L"Resources/Musics/Ujabes - Kafka On The Shore.mp3");

	playingSongName = new PlayingSongName();
	playingSongName->SetText("Ujabes - Kafka On The Shore");
	AttachObject(playingSongName);
	playingSongName->commandLists[0]->Start();
}

SickRoom::~SickRoom() {}

void SickRoom::OnUpdate() {
	if (paused) {

	}
	else if (objectView) {
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) {
			viewingObject->SetIsEnable(false);
			filter->SetIsEnable(false);

			objectView = false;
		}
	}
	else {
		Vec2F catPos = cat->GetComponent<Transform>()->GetPos();

		if (-5.9f < catPos.x && catPos.x < 5.9f) {
			GetMainCamera()->SetPosX(catPos.x);
		}


		if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_STAY && cat->GetComponent<Transform>()->GetPos().y < 0.f) {
			cat->GetComponent<Transform>()->Translate(Vec2F(0, 3.f) * RG2R_TimeM->GetDeltaTime());
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_BACK);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_EXIT) {
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_NONE);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_STAY && cat->GetComponent<Transform>()->GetPos().y > -1.8f) {
			cat->GetComponent<Transform>()->Translate(Vec2F(0, -3.f) * RG2R_TimeM->GetDeltaTime());
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_FORWARD);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_EXIT) {
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_NONE);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_STAY && cat->GetComponent<Transform>()->GetPos().x < 11.f) {
			cat->GetComponent<Transform>()->Translate(Vec2F(3.f, 0) * RG2R_TimeM->GetDeltaTime());
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_RIGHT);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_EXIT) {
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_NONE);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_STAY && cat->GetComponent<Transform>()->GetPos().x > -11.f) {
			cat->GetComponent<Transform>()->Translate(Vec2F(-3.f, 0) * RG2R_TimeM->GetDeltaTime());
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_LEFT);
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_EXIT) {
			cat->SetWalkDirection(WalkDirection::WALKDIRECTION_NONE);
		}

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
			paused = true;
			RG2R_GameM->PauseM->SetIsEnable(true);
		}
	}

	//Object* object = curtain;

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