#pragma  once

#include "Graphic.h"

unsigned int Graphic::viewport_width;
unsigned int Graphic::viewport_height;

ConstantBuffer Graphic::constant_camera;
ConstantBuffer Graphic::constant_model;
ConstantBuffer Graphic::constant_material;
ConstantBuffer Graphic::constant_light;
ConstantBuffer Graphic::constant_skybox;
ConstantBuffer Graphic::constant_cubemap;
ConstantBuffer Graphic::constant_animationbone;

FrameBuffer    Graphic::frame_shadowcubemaps[NUM_MAX_POINT_LIGHT];
FrameBuffer    Graphic::frame_cubemap;
FrameBuffer    Graphic::frame_irradiance;
FrameBuffer    Graphic::frame_specular;
FrameBuffer    Graphic::frame_brdf;
FrameBuffer    Graphic::frame_image;