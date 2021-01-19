#pragma once
#include "DebugLog.h"
#include "Object3D.h"
#include "EntityMaster.h"


class Monster : public Object3D
{
public:
	Monster() {};
	~Monster() {};

	void init();
	void update();
private:
	Engine::Object3DPointer *obj_player;
	Vec3f * pos_player;
	Vec3f * pos_enemy;
};

inline void Monster::init() {
	std::list<Engine::Object3DPointer *> obj_list = *Engine::EntityMaster::ObjectList;
	obj_player = *( std::find_if(obj_list.begin(), obj_list.end(), [&](Engine::Object3DPointer* e) {return e->pointer->name == "GoodGuy"; }));

	pos_player = &(obj_player->pointer->pos);
	pos_enemy = &(this->pos);
}

inline void Monster::update() {
	if (pos_enemy->x >= pos_player->x) {
		pos_enemy->x -= 0.01f;
	}
	else {
		pos_enemy->x += 0.01f;
	}

	if (pos_enemy->y >= pos_player->y) {
		pos_enemy->y -= 0.01f;
	}
	else {
		pos_enemy->y += 0.01f;
	}
}
