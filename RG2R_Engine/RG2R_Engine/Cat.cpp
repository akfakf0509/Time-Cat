#include "stdafx.h"
#include "Cat.h"
#include "AnimationRenderer.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"
#include "RandomGenerator.h"

Cat::Cat() {
}

Cat::~Cat() {
}

void Cat::OnStart() {
	idle = CreateChildObject();
	idle->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/CatAnimations/Cat.png");
	idle->GetComponent<Transform>()->SetAnchor(idle->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());

	forward = CreateChildObject();
	forward->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/WalkForward")
		->SetInterval(0.1f);
	forward->GetComponent<Transform>()
		->SetAnchor(forward->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter());

	back = CreateChildObject();
	back->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/WalkBack")
		->SetInterval(0.1f);
	back->GetComponent<Transform>()
		->SetAnchor(back->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter());

	side = CreateChildObject();
	side->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/Walk")
		->SetInterval(0.1f);
	side->GetComponent<Transform>()
		->SetAnchor(side->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter());

	ear = idle->CreateChildObject();
	ear->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/EarAnimation")
		->SetIsLoop(false)
		->SetInterval(0.05f);
	ear->GetComponent<Transform>()->SetAnchor(ear->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter());

	eyes.push_back(idle->CreateChildObject());
	eyes[0]->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/CatAnimations/Eye/RightEye.png");

	eyes.push_back(idle->CreateChildObject());
	eyes[1]->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/CatAnimations/Eye/LeftEye.png");

	for (auto iter : eyes) {
		eye_transforms.push_back(iter->GetComponent<Transform>());

		iter->GetComponent<Transform>()
			->SetAnchor(iter->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());
	}
}

void Cat::OnUpdate() {
	for (int i = 0; i < 2; i++) {
		auto distance = RG2R_InputM->GetMouseWorldPos() - eye_transforms[i]->GetWorldPos() + Vec2F(-0.36f + i * 0.35f, -0.45f);

		eye_transforms[i]->SetPos(distance.Normalize() / 100);
	}

	ear_animation_interval -= RG2R_TimeM->GetDeltaTime();

	if (ear_animation_interval <= 0) {
		auto randomgenerator = new RandomGenerator();
		ear_animation_interval = randomgenerator->GetInt(1, 5);

		ear->GetComponent<AnimationRenderer>()
			->Play();
	}

	if (walkDirection != perWalkDirection) {
		if (walkDirection == WalkDirection::WALKDIRECTION_NONE) {
			SetIsFlipX(false);

			idle->SetIsEnable(true);
			forward->SetIsEnable(false);
			back->SetIsEnable(false);
			side->SetIsEnable(false);
		}
		else if (walkDirection == WalkDirection::WALKDIRECTION_RIGHT || walkDirection == WalkDirection::WALKDIRECTION_LEFT) {
			if (walkDirection == WalkDirection::WALKDIRECTION_RIGHT) {
				SetIsFlipX(false);
			}
			else if (walkDirection == WalkDirection::WALKDIRECTION_LEFT) {
				SetIsFlipX(true);
			}

			idle->SetIsEnable(false);
			forward->SetIsEnable(false);
			back->SetIsEnable(false);
			side->SetIsEnable(true);
		}
		else if (walkDirection == WalkDirection::WALKDIRECTION_FORWARD) {
			idle->SetIsEnable(false);
			forward->SetIsEnable(true);
			back->SetIsEnable(false);
			side->SetIsEnable(false);
		}
		else if (walkDirection == WalkDirection::WALKDIRECTION_BACK) {
			idle->SetIsEnable(false);
			forward->SetIsEnable(false);
			back->SetIsEnable(true);
			side->SetIsEnable(false);
		}
	}

	perWalkDirection = walkDirection;
}

void Cat::SetWalkDirection(WalkDirection walkDirection) {
	this->walkDirection = walkDirection;
}

WalkDirection Cat::GetWalkDirection() {
	return walkDirection;
}