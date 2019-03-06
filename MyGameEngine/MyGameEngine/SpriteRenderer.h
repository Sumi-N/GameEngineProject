#pragma once

#include "Object2D.h"
#include "SmartPointers.h"
#include "../GLib/GLib.h"

class SpriteRenderer {
public:
	void update();
	void release();
	bool createSprite(const char * i_pFilename);
	void * loadFile(const char*, size_t &);
public:
	GLib::Sprites::Sprite * sprite;
	GLib::Point2D offset;
	Engine::ObservingPointer<Object2D> pointer;
};