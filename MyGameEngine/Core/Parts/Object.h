#pragma once
#include "Define.h"

#ifdef _USEINTRINSIC_
//__declspec(align(16))
#endif // _USEINTRINSIC_
class Object
{
public:

	Object();

	Vec3f pos, scale, rot;
	Vec3f vel, acc;
	Vec3f angvel, angacc;

	void Translate(Vec3f i_pos) {this->pos = i_pos;}

	virtual void Boot();
	virtual void Init();
	virtual void Update(float i_dt);
	virtual void CleanUp();
};

inline Object::Object()
{
	pos    = Vec3f(0.0, 0.0, 0.0);
	scale  = Vec3f(1.0, 1.0, 1.0);
	rot    = Vec3f(0.0, 0.0, 0.0);
			 
	vel    = Vec3f(0.0, 0.0, 0.0);
	acc    = Vec3f(0.0, 0.0, 0.0);
	angvel = Vec3f(0.0, 0.0, 0.0);
	angacc = Vec3f(0.0, 0.0, 0.0);
}

inline void Object::Boot() {}

inline void Object::Init() {}

inline void Object::Update(float i_dt) 
{
	pos += i_dt * vel;
}

inline void Object::CleanUp() {}


