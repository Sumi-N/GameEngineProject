#pragma once
#include "Define.h"

#ifdef _USEINTRINSIC_
//__declspec(align(16))
#endif // _USEINTRINSIC_
class Object
{
public:
	Vec3f pos, scale, rot;
	Vec3f vel, acc;
	Vec3f angvel, angacc;

	void Translate(Vec3f i_pos) {this->pos = i_pos;}

	virtual void Init();
	virtual void Update(float i_dt);
	virtual void CleanUp();
};

inline void Object::Init() {}

inline void Object::Update(float i_dt) 
{
	pos += i_dt * vel;
}

inline void Object::CleanUp() {}


