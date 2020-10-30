#pragma once

#include "Object.h"
#include "Texture.h"

#include <vector>

class WebToon :
	public Object
{
private:
	std::vector<Texture*> textures;
public:
	WebToon();
	~WebToon();


};

