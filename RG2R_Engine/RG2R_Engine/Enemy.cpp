#include "stdafx.h"
#include "Enemy.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Player.h"
#include "CollisionInfo.h"

Enemy::Enemy() {
	SetTag("Enemy");

	GetComponent<Transform>()
		->SetAnchor(16, 16);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Enemy.png");
	AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f)
		->SetHeightSize(0.25f);
	AttachComponent<Rigidbody>();
}

Enemy::~Enemy() {
}

void Enemy::OnUpdate() {
	if (target) {
		Vec2F target_direction = target->GetComponent<Transform>()->GetPos() - GetComponent<Transform>()->GetPos();

		target_direction = target_direction.Normalize();

		GetComponent<Transform>()->Translate(target_direction * 0.01f);
	}
}

void Enemy::OnCollisionStay(CollisionInfo* collision) {
	if (collision->object->GetTag() == "Bullet") {
		SetIsEnable(false);
		collision->object->SetIsEnable(false);
		//Destroy();
	}
}

int Enemy::GetHp()
{
	return hp;
}

Enemy* Enemy::SetTarget(Object* target) {
	this->target = target;

	return this;
}

Enemy * Enemy::SetHp(int hp)
{
	this->hp = hp;

	return this;
}
