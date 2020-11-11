#include "stdafx.h"
#include "ButtonObject.h"

#include "SpriteRenderer.h"
#include "TextRenderer.h"

ButtonObject::ButtonObject() {
	text = CreateChildObject();
	text->AttachComponent<TextRenderer>()
		->SetText("Button");
}

ButtonObject::~ButtonObject() {
}