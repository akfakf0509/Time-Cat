#include "stdafx.h"
#include "PlayingSongName.h"

#include "TextRenderer.h"
#include "Transform.h"
#include "Engine.h"

PlayingSongName::PlayingSongName() {
	CommandList* commandlist = new CommandList();
	commandlist->PushCommand([=]() { 
		targetPos = Vec2F(-5.1f, -2.7f);
	}, 0)
		->PushCommand([=]() {
		targetPos = Vec2F(-5.1f, -3.1f);
	}, 3);

	commandLists.push_back(commandlist);

	AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Song Writer - Song Name")
		->SetSize(30)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	GetComponent<Transform>()
		->SetIsRelative(false)
		->SetPos(-5.1f, -3.1f);
}

PlayingSongName::~PlayingSongName() {
}

void PlayingSongName::OnUpdate() {
	GetComponent<Transform>()->SetPos(GetComponent<Transform>()->GetPos() + (targetPos - GetComponent<Transform>()->GetPos()) * RG2R_TimeM->GetDeltaTime() * 6.f);
}

void PlayingSongName::SetText(const std::string& songName) {
	GetComponent<TextRenderer>()
		->SetText(songName);
}