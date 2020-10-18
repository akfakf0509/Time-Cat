#include "stdafx.h"
#include "Ingame.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "PistolBullet.h"
#include "RandomGenerator.h"

Ingame::Ingame() {
	background = CreateObject();

	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Background.png");

	background->GetComponent<Transform>()
		->SetAnchor(background->GetComponent<SpriteRenderer>()->GetTexture()->GetSize().width / 2, background->GetComponent<SpriteRenderer>()->GetTexture()->GetSize().height / 2);

	player = new Player();
	AttachObject(player);
}

Ingame::~Ingame() {
}

void Ingame::OnUpdate() {
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER) {
		player->Shoot();
	}

	for (auto enemy : enemys) {
		enemy->GetComponent<Transform>()->LookAt(player);
	}

	auto random = new RandomGenerator();

	if (random->GetInt(0, 100) == 0) {
		SpawnEnemy();
	}
}

Ingame* Ingame::SpawnEnemy() {
	auto random = new RandomGenerator();

	auto new_enemy = new Enemy();
	new_enemy->SetTarget(player);
	enemys.push_back(new_enemy);
	AttachObject(new_enemy);

	switch (random->GetInt(0, 3))
	{
	case 0:
		new_enemy->GetComponent<Transform>()->SetPos(6, 3);
		break;
	case 1:
		new_enemy->GetComponent<Transform>()->SetPos(-6, -3);
		break;
	case 2:
		new_enemy->GetComponent<Transform>()->SetPos(6, -3);
		break;
	case 3:
		new_enemy->GetComponent<Transform>()->SetPos(-6, 3);
	default:
		break;
	}

	return this;
}