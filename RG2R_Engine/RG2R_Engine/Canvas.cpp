#include "stdafx.h"
#include "Canvas.h"

#include "UIElement.h"

Canvas::Canvas() {
}

Canvas::~Canvas() {
}

void Canvas::OnStart() {
	for (auto tmp : GetChilds()) {
		UIElement* iter = (UIElement*)tmp;

		iter->clickedOn;
	}
}

void Canvas::OnUpdate() {

}