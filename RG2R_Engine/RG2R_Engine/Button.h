#pragma once
#include "Component.h"
#include "Texture.h"

class Transform;
class SpriteRenderer;
class BoxCollider;
class CircleCollider;

class Button :
	public Component
{
private:
	Transform* transform;
	SpriteRenderer* spriterenderer;
	BoxCollider* boxcollider;
	CircleCollider* circleCollider;

	Texture* normalTexture = nullptr;
	Texture* hoverTexture = nullptr;
	Texture* pushedTexture = nullptr;
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

	Button* SetNormalTexture(Texture*);
	Button* SetHoverTexture(Texture*);
	Button* SetPushedTexture(Texture*);
	Button* SetNormalTexture(const std::string&);
	Button* SetHoverTexture(const std::string&);
	Button* SetPushedTexture(const std::string&);

	Texture* GetNormalTexture();
	Texture* GetHoverTexture();
	Texture* GetPushedTexture();
};

