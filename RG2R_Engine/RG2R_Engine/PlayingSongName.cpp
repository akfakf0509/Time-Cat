#include "stdafx.h"
#include "PlayingSongName.h"

#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"

PlayingSongName::PlayingSongName() {
	CommandList* commandlist = new CommandList();
	commandlist->PushCommand([=]() { 
		targetPos = Vec2F(-4.9f, -2.6f);
	}, 1)
		->PushCommand([=]() {
		targetPos = Vec2F(-4.9f, -3.3f);
	}, 5);

	commandLists.push_back(commandlist);

	GetComponent<Transform>()
		->SetIsRelative(false)
		->SetPos(-4.9f, -3.3f);

	songName = CreateChildObject();
	songName->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Song Writer - Song Name")
		->SetSize(30)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	songName->GetComponent<Transform>()
		->SetPos(0.3f, 0);

	record = CreateChildObject();
	record->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Record.png");
	record->GetComponent<Transform>()
		->SetAnchor(record->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.1f, 0.1f);

	record->onUpdateListener = [=]() {
		record->GetComponent<Transform>()
			->Rotate(100 * RG2R_TimeM->GetDeltaTime());
	};
}

PlayingSongName::~PlayingSongName() {
}

void PlayingSongName::OnUpdate() {
	GetComponent<Transform>()->SetPos(GetComponent<Transform>()->GetPos() + (targetPos - GetComponent<Transform>()->GetPos()) * RG2R_TimeM->GetDeltaTime() * 4.f);
}

void PlayingSongName::SetText(const std::string& songName) {
	this->songName->GetComponent<TextRenderer>()
		->SetText(songName);
}