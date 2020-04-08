#pragma  once

#include "Graphic.h"

ConstantBuffer Graphic::constant_camera;
ConstantBuffer Graphic::constant_model;
ConstantBuffer Graphic::constant_material;
ConstantBuffer Graphic::constant_light;
ConstantBuffer Graphic::constant_skybox;
ConstantBuffer Graphic::constant_shadow;

FrameBuffer    Graphic::frame_shadow[MAX_POINT_LIGHT_NUM];
FrameBuffer    Graphic::frame_mirror;
FrameBuffer    Graphic::frame_cubemap;