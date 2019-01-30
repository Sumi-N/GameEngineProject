#pragma once
#include "../GLib/GLib.h"

class SpriteRenderer {
public:
	GLib::Sprites::Sprite * sprite;
	void draw();
	bool createSprite(const char * i_pFilename);
	void * loadFile(const char*, size_t &);
};