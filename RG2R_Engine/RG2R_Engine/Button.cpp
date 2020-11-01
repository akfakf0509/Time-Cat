#include "stdafx.h"
#include "Button.h"
#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::OnStart() {
	transform = GetOwner()->GetComponent<Transform>();
	spriterenderer = GetOwner()->GetComponent<SpriteRenderer>();
	circleCollider = GetOwner()->GetComponent<CircleCollider>();
	boxcollider = GetOwner()->GetComponent<BoxCollider>();

	if (effectType == ButtonEffectType::ImageChange) {
		if (spriterenderer == nullptr) {
			cout << "[" << GetOwner()->GetName() << "] " << "<Button> : Sprite Renderer is nullptr" << endl;
			SetIsEnable(false);
			return;
		}

		if (normalTexture == nullptr) {
			normalTexture = spriterenderer->GetTexture();
		}
		if (hoverTexture == nullptr) {
			hoverTexture = spriterenderer->GetTexture();
		}
		if (pushedTexture == nullptr) {
			pushedTexture = spriterenderer->GetTexture();
		}
	}
}

void Button::OnUpdate() {
	Vec2F position = transform->GetPos();
	Vec2F mouseposition = RG2R_InputM->GetMouseWorldPos();

	std::function<void()> checkMouseStat = [=]() {
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER) {
			if (effectType == ButtonEffectType::ImageChange) {
				spriterenderer->SetTexture(pushedTexture);
			}
			else if (effectType == ButtonEffectType::ScaleChange) {
				GetOwner()->GetComponent<Transform>()->SetScale(pushedScale);
			}
			GetOwner()->OnClickEnter();
			ApplyListener(GetOwner()->onClickEnter);
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY) {
			GetOwner()->OnClickStay();
			ApplyListener(GetOwner()->onClickStay);
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) {
			if (effectType == ButtonEffectType::ImageChange) {
				spriterenderer->SetTexture(hoverTexture);
			}
			else if (effectType == ButtonEffectType::ScaleChange) {
				GetOwner()->GetComponent<Transform>()->SetScale(hoverScale);
			}
			GetOwner()->OnClickExit();
			ApplyListener(GetOwner()->onClickExit);
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE) {
			if (effectType == ButtonEffectType::ImageChange) {
				spriterenderer->SetTexture(hoverTexture);
			}
			else if (effectType == ButtonEffectType::ScaleChange) {
				GetOwner()->GetComponent<Transform>()->SetScale(hoverScale);
			}
		}
	};

	if (boxcollider != nullptr) {
		if (position.x - boxcollider->GetWidthSize() / 2 <= mouseposition.x && mouseposition.x <= position.x + boxcollider->GetWidthSize() / 2 &&
			position.y - boxcollider->GetHeightSize() / 2 <= mouseposition.y && mouseposition.y <= position.y + boxcollider->GetHeightSize() / 2) {
			checkMouseStat();
		}
		else {
			if (effectType == ButtonEffectType::ImageChange) {
				spriterenderer->SetTexture(normalTexture);
			}
			else if (effectType == ButtonEffectType::ScaleChange) {
				GetOwner()->GetComponent<Transform>()->SetScale(normalScale);
			}
		}
	}
	else if (circleCollider != nullptr) {
		if (circleCollider->GetRad() >= position.Distance(mouseposition)) {
			checkMouseStat();
		}
		else {
			if (effectType == ButtonEffectType::ImageChange) {
				spriterenderer->SetTexture(normalTexture);
			}
			else if (effectType == ButtonEffectType::ScaleChange) {
				GetOwner()->GetComponent<Transform>()->SetScale(normalScale);
			}
		}
	}
	else {
		Rect rect = spriterenderer->GetRealArea();

		if (position.x - rect.right / INCH_PER_DISTANCE / 2 <= mouseposition.x && mouseposition.x <= position.x + rect.right / INCH_PER_DISTANCE  / 2 &&
			position.y - rect.bottom / INCH_PER_DISTANCE / 2 <= mouseposition.y && mouseposition.y <= position.y + rect.bottom / INCH_PER_DISTANCE / 2) {
			checkMouseStat();
		}
		else {
			if (effectType == ButtonEffectType::ImageChange) {
				spriterenderer->SetTexture(normalTexture);
			}
			else if (effectType == ButtonEffectType::ScaleChange) {
				GetOwner()->GetComponent<Transform>()->SetScale(normalScale);
			}
		}
	}
}

void Button::Render()
{
}

void Button::Render(ViewRenderData &)
{
}

Button* Button::SetButtonEffectType(ButtonEffectType effectType) {
	this->effectType = effectType;

	return this;
}

Button* Button::SetNormalTexture(Texture* texture) {
	normalTexture = texture;

	return this;
}

Button* Button::SetNormalTexture(const std::string& path) {
	normalTexture = RG2R_TextureM->Load(path);

	return this;
}

Button* Button::SetHoverTexture(Texture* texture) {
	hoverTexture = texture;

	return this;
}

Button* Button::SetHoverTexture(const std::string& path) {
	hoverTexture = RG2R_TextureM->Load(path);

	return this;
}

Button* Button::SetPushedTexture(Texture* texture) {
	pushedTexture = texture;

	return this;
}

Button* Button::SetPushedTexture(const std::string& path) {
	pushedTexture = RG2R_TextureM->Load(path);

	return this;
}

Button* Button::SetNormalScale(Vec2F scale) {
	normalScale = scale;

	return this;
}

Button* Button::SetHoverScale(Vec2F scale) {
	hoverScale = scale;

	return this;
}

Button* Button::SetPushedScale(Vec2F scale) {
	pushedScale = scale;

	return this;
}

Texture* Button::GetNormalTexture() {
	return normalTexture;
}

Texture* Button::GetHoverTexture() {
	return hoverTexture;
}

Texture* Button::GetPushedTexture() {
	return pushedTexture;
}

Vec2F Button::GetNormalScale() {
	return normalScale;
}

Vec2F Button::GetHoverScale() {
	return hoverScale;
}

Vec2F Button::GetPushedScale() {
	return pushedScale;
}

ButtonEffectType Button::GetButtonEffectType() {
	return effectType;
}