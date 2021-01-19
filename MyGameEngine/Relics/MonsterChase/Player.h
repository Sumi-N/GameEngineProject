#pragma once
#include "Object3D.h"
#include "Physics3D.h"


class Player : public Object3D
{
public:
	void init();
	void update();
	
private:
	Physics3D * phy_player;
};

inline void Player::init() {
	std::list<Physics3D *> phy_list = Engine::EntityMaster::Physics->getList();
	phy_player = *( std::find_if(phy_list.begin(), phy_list.end(), [](Physics3D * e) {auto objpointer = e->pointer; return objpointer->name == "GoodGuy"; }));
}

inline void Player::update() {
	if ((InputMap::Map)->at(68) == true) {
		phy_player->addForce(Vec3f(5, 0, 0));
	}
	else if ((InputMap::Map)->at(65) == true) {
		phy_player->addForce(Vec3f(-5, 0, 0));
	}
	else if ((InputMap::Map)->at(87) == true) {
		phy_player->addForce(Vec3f(0, 5, 0));
	}
	else if ((InputMap::Map)->at(83) == true) {
		phy_player->addForce(Vec3f(0, -5, 0));
	}
}
