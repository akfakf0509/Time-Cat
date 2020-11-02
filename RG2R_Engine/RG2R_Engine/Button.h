#pragma once
#include "Component.h"
#include "ButtonEffectType.h"
#include "Texture.h"

class Transform;
class SpriteRenderer;
class BoxCollider;
class CircleCollider;

class Button :
	public Component
{
private:
	ButtonEffectType effectType = ButtonEffectType::ImageChange;

	Transform* transform;
	SpriteRenderer* spriterenderer;
	BoxCollider* boxcollider;
	CircleCollider* circleCollider;

	Texture* normalTexture = nullptr;
	Texture* hoverTexture = nullptr;
	Texture* pushedTexture = nullptr;

	Vec2F normalScale = Vec2F(1, 1);
	Vec2F hoverScale = Vec2F(1.1f, 1.1f);
	Vec2F pushedScale = Vec2F(1.05f, 1.05f);
public:
	Button();
	~Button();

	void Update() {}
	std::type_index GetID(void) override { return typeid(Button); }
	static std::type_index GetFamilyID(void) { return typeid(Button); }

	void OnStart();
	void OnUpdate();
	void Render();
	void Render(ViewRenderData&);

	Button* SetButtonEffectType(ButtonEffectType);

	Button* SetNormalTexture(Texture*);
	Button* SetHoverTexture(Texture*);
	Button* SetPushedTexture(Texture*);
	Button* SetNormalTexture(const std::string&);
	Button* SetHoverTexture(const std::string&);
	Button* SetPushedTexture(const std::string&);

	Button* SetNormalScale(Vec2F);
	Button* SetHoverScale(Vec2F);
	Button* SetPushedScale(Vec2F);

	Texture* GetNormalTexture();
	Texture* GetHoverTexture();
	Texture* GetPushedTexture();

	Vec2F GetNormalScale();
	Vec2F GetHoverScale();
	Vec2F GetPushedScale();

	ButtonEffectType GetButtonEffectType();
};