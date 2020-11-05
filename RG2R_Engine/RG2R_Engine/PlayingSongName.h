#pragma once
#include "Object.h"
class PlayingSongName :
	public Object
{
private:
	Vec2F targetPos = { -4.9f, -3.3f };

private:
	Object* songName;
	Object* record;
public:
	PlayingSongName();
	~PlayingSongName();

	void OnUpdate();

	void SetText(const std::string&);
};

