#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "SpriteRenderer.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(float _width, float _height) {
	area = { _width, _height };
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::OnStart() {
	SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

	if (spriteRenderer != nullptr) {
		area = { spriteRenderer->GetRealArea().right / INCH_PER_DISTANCE, spriteRenderer->GetRealArea().bottom /INCH_PER_DISTANCE };
	}
}

Vec2F BoxCollider::GetArea() {
	return area;
}

float BoxCollider::GetWidthSize() {
	return area.x;
}

float BoxCollider::GetHeightSize() {
	return area.y;
}

BoxCollider* BoxCollider::SetArea(Vec2F area) {
	this->area = area;

	return this;
}

BoxCollider* BoxCollider::SetArea(float width, float height) {
	this->area = { width, height };

	return this;
}

BoxCollider* BoxCollider::SetWidthSize(float _width) {
	area.x = _width;

	return this;
}

BoxCollider* BoxCollider::SetHeightSize(float _height) {
	area.y = _height;

	return this;
}