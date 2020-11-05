#include "stdafx.h"
#include "TextAnimation.h"

#include "TextRenderer.h"
#include "Engine.h"

TextAnimation::TextAnimation() {}

TextAnimation::~TextAnimation() {}

void TextAnimation::OnStart() {
	textRenderer = GetOwner()->GetComponent<TextRenderer>();

	if (textRenderer == nullptr) {
		std::cout << "TextRenderer is nullptr" << std::endl;

		SetIsEnable(false);
	}
	
	currentDelay = delay;
}

void TextAnimation::Update() {
	if (currentDelay <= 0) {
		currentinterval -= RG2R_TimeM->GetDeltaTime();

		if (currentinterval <= 0) {
			nowText = textRenderer->GetText();
			currentinterval = interval;

			if (nowText != targetText) {
				std::string newtext = targetText;
				newtext.resize(nowText.size() + 1);

				textRenderer->SetText(newtext);
			}
		}
	}
	else {
		currentDelay -= RG2R_TimeM->GetDeltaTime();
	}
}

TextAnimation* TextAnimation::SetTargetText(const std::string& text) {
	targetText = text;

	return this;
}

TextAnimation* TextAnimation::SetInterval(float interval) {
	this->interval = interval;
	this->currentinterval = interval;

	return this;
}

TextAnimation* TextAnimation::SetDelay(float delay) {
	this->delay = delay;

	return this;
}

TextAnimation* TextAnimation::Reset() {
	textRenderer->SetText("");
	currentDelay = delay;

	return this;
}

std::string TextAnimation::GetTargetText() {
	return targetText;
}

float TextAnimation::GetInterval() {
	return interval;
}