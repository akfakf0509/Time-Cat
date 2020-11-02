#pragma once
#include "Object.h"
class PlayingSongName :
	public Object
{
private:
	Vec2F targetPos = { -5.1f, -3.1f };
public:
	PlayingSongName();
	~PlayingSongName();

	void OnUpdate();

	void SetText(const std::string&);
};

