#pragma once

#include "Define.h"
#include "PremadeObject.h"

namespace Tempest
{

	class Sphere : public PremadeObjebct
	{
	public:
		void Boot() override;
		void Init() override;
		void Update(float) override;

		//Vec3f axis;
	};

	inline void Sphere::Boot()
	{
		PremadeObjebct::Boot();

		mesh->Load(PATH_SUFFIX BIN_MESH_PATH FILENAME_SPHERE);
	}

	inline void Sphere::Init()
	{
		PremadeObjebct::Init();
	}

	inline void Sphere::Update(float i_dt)
	{
		//if (UserInput.QueryKey(VirtualKey::KEY_SPACE) == InputState::Pressing)
		//{
		//	axis.Normalize();
		//	Quaternionf axisq = Quaternionf::AngleAxis(0.01f, axis);
		//	Quaternionf current = Quaternionf::EulerToQuaternion(rot.x, rot.y, rot.z);
		//	current = axisq * current;
		//	Vec3f result1 = Quaternionf::QuaternionToEuler(current);
		//	rot = result1;
		//}
	}

}