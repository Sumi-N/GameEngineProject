#pragma once

#include "Define.h"
#include "PremadeObject.h"

class Sphere : public PremadeObjebct
{
public:
	void Boot() override;
	void Init() override;
	void Update(float) override;

	Vec3f axis1;
};

inline void Sphere::Boot()
{
	PremadeObjebct::Boot();

	mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_SPHERE);
}

inline void Sphere::Init()
{
	PremadeObjebct::Init();
}

inline void Sphere::Update(float i_dt)
{
	if (UserInput.QueryKey(VirtualKey::KEY_SPACE) == InputState::Pressing)
	{
		axis1.Normalize();
		Quaternionf axisq = Quaternionf::AngleAxis(0.01f, axis1);
		Quaternionf current = Quaternionf::EulerToQuaternion(rot.x, rot.y, rot.z);
		current = axisq * current;
		Vec3f result1 = Quaternionf::QuaternionToEuler(current);
		rot = result1;
	}
}