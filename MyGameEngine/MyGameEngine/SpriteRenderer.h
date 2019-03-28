#pragma once

#include "Object3D.h"
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
	Engine::ObservingPointer<Object3D> pointer;
	void PassAABBInfo();

private:
	float spriteWidth;
	float spriteHeight;
};