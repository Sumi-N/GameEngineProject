#pragma once
#include "Define.h"
#include "Object.h"

class Light
{
public:
	Vec3f intensity;
};

class AmbientLight : public Light
{

};

class PointLight : public Light
{
public:
	Vec3f pos;
};

class DirectionalLight : public Light
{
public:
	Vec3f direction;
};