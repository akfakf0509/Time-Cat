#include "stdafx.h"
#include "Slider.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Engine.h"

Slider::Slider() {
	bar = CreateChildObject();
	bar->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Setting/SlideBar.png");
	bar->GetComponent<Transform>()
		->SetAnchor(bar->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());

	button = bar->CreateChildObject();
	button->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Setting/SlideButton.png");
	button->GetComponent<Transform>()
		->SetAnchor(button->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	button->AttachComponent<BoxCollider>()
		->SetArea(1, 1);
	button->AttachComponent<Button>();
	button->onClickStay = [=]() {
		Transform* transform = button->GetComponent<Transform>();
		Rect rect = bar->GetComponent<SpriteRenderer>()->GetVisibleArea();
		Vec2F distance = RG2R_InputM->GetMouseWorldPos() - bar->GetComponent<Transform>()->GetWorldPos();


		if (-rect.right / INCH_PER_DISTANCE / 2 * GetComponent<Transform>()->GetScale().x + GetComponent<Transform>()->GetWorldPos().x < RG2R_InputM->GetMouseWorldPos().x && 
			RG2R_InputM->GetMouseWorldPos().x < rect.right / INCH_PER_DISTANCE / 2 * GetComponent<Transform>()->GetScale().x + GetComponent<Transform>()->GetWorldPos().x) {
			transform->SetPos(distance.x / GetComponent<Transform>()->GetScale().x, 0);
		}

		value = (rect.right / INCH_PER_DISTANCE / 2 * GetComponent<Transform>()->GetScale().x + distance.x) / (rect.right / INCH_PER_DISTANCE * GetComponent<Transform>()->GetScale().x);

		if (value < 0) {
			value = 0;
		}
		else if (value > 1) {
			value = 1;
		}
	};
}

Slider::~Slider() {
}

Slider* Slider::SetValue(float value) {
	this->value = value;

	return this;
}

float Slider::GetValue() {
	return value;
}