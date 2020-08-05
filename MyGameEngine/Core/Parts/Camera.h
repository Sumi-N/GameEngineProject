#pragma once
#include "Define.h"
#include "Object.h"
#include "MeshComponent.h"
#include "EffectComponent.h"

class Camera : public Object 
{
public:
	Mat4f view, perspective, orthographics;
	Mat4f view_perspective_mat;
public:

	Camera()
	{
		forwardvec = Vec3f(0, 0, -1);
		upvec = Vec3f(0, 1, 0);
		rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));

		// The parameters for lookAt function are position, target, up vector
		// target is equal to forwardvector + position;
		view = Mat4f::LookAt(pos, pos + forwardvec, upvec);

		perspective   = Mat4f::Perspective(FOV, (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEARCLIP, FARCLIP);
		orthographics = Mat4f::Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, NEARCLIP, FARCLIP);
	}

	Vec3f GetForwardVec(){return forwardvec; }
	Vec3f GetRightVec()  {return rightvec; }
	Vec3f GetUpVec()     {return upvec; }

	void Boot() override;
	void Init() override;
	void Update(float) override;

	void MoveCamera(float, Vec3f&);
	void RotateAround(float, Vec3f&);

protected:
	Vec3f forwardvec, upvec, rightvec;

private:
	OwningPointer<MeshComponent> mesh;
	OwningPointer<EffectComponent> effect;
};

inline void Camera::Boot()
{
	Object::Boot();

	//mesh = ObjectFactory<MeshComponent>::Create();
	//OwningPointer<MeshComponent>::Create(mesh);
	//mesh->Load(PATH_SUFFIX MESH_PATH FILENAME_SPHERE);
	//OwningPointer<MaterialAttribute> material;
	//material = ObjectFactory<MaterialAttribute>::Create();
	//mesh->SetMaterial(material);
	//mesh->owner = Entity::Query(this).p;
	//Entity::RegisterMeshComponent(mesh);

	const char* shaderpaths[] =
	{
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_VERT,
		nullptr,
		nullptr,
		nullptr,
		PATH_SUFFIX SHADER_PATH DISNEY_PBR_FRAG,
	};

	//effect = ObjectFactory<EffectComponent>::Create();
	//OwningPointer<MeshComponent>::Create(effect);
	//effect->owner = Entity::Query(this).p;
	//effect->RegisterShaderPath(shaderpaths);
}

inline void Camera::Init()
{
	Object::Init();
}

inline void Camera::Update(float i_dt)
{
	Object::Update(i_dt);

	pos += (float)i_dt * vel;
	vel = Vec3f(0, 0, 0);

	view = Mat4f::LookAt(pos, pos + forwardvec, upvec);
	view_perspective_mat = perspective * view;
}

inline void Camera::MoveCamera(float amount, Vec3f& dir)
{
	vel = amount * dir;
}

inline void Camera::RotateAround(float amount, Vec3f& axis)
{

	forwardvec = forwardvec.Rotate(axis, amount);
	upvec = upvec.Rotate(axis, amount);

	rightvec = Vec3f::Normalize(forwardvec.Cross(upvec));
}