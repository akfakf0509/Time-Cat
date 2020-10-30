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
	ear = CreateObject();
	ear->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/EarAnimation")
		->SetIsLoop(false)
		->SetInterval(0.05f);
	ear->GetComponent<Transform>()->SetAnchor(ear->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter());

	eyes.push_back(CreateObject());
	eyes[0]->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/CatAnimations/Eye/RightEye.png");

	eyes.push_back(CreateObject());
	eyes[1]->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/CatAnimations/Eye/LeftEye.png");

	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/CatAnimations/Cat.png");
	GetComponent<Transform>()
		->SetAnchor(GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());

	AttachChild(ear);

	for (auto iter : eyes) {
		eye_transforms.push_back(iter->GetComponent<Transform>());

		iter->GetComponent<Transform>()
			->SetAnchor(iter->GetComponent<SpriteRenderer>()->GetRealArea().GetCenter());

		AttachChild(iter);
	}
}

void Cat::OnUpdate() {
	for (int i = 0; i < 2; i++) {
		auto distance = RG2R_InputM->GetMouseWorldPos() - eye_transforms[i]->GetPos() + Vec2F(-0.36f + i * 0.35f, -0.45f);

		eye_transforms[i]->SetPos(distance.Normalize() / 100);
	}

	ear_animation_interval -= RG2R_TimeM->GetDeltaTime();

	if (ear_animation_interval <= 0) {
		auto randomgenerator = new RandomGenerator();
		ear_animation_interval = randomgenerator->GetInt(1, 5);

		ear->GetComponent<AnimationRenderer>()
			->Play();
	}
}