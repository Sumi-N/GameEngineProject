#pragma  once

#include "Graphic.h"

unsigned int Graphic::ViewportWidth;
unsigned int Graphic::ViewportHeight;

ConstantBuffer Graphic::ConstBufferCamera;
ConstantBuffer Graphic::ConstBufferModel;
ConstantBuffer Graphic::ConstBufferMaterial;
ConstantBuffer Graphic::ConstBufferLight;
ConstantBuffer Graphic::ConstBufferSkybox;
ConstantBuffer Graphic::ConstBufferCubeMap;
ConstantBuffer Graphic::ConstBufferAnimationBone;

ConstantData::Camera Graphic::ConstDataCamera;

FrameBuffer    Graphic::FrameBufferShadowMaps[NUM_MAX_POINT_LIGHT];
FrameBuffer    Graphic::FrameBufferCubeMap;
FrameBuffer    Graphic::FrameBufferIrradiance;
FrameBuffer    Graphic::FrameBufferSpecular;
FrameBuffer    Graphic::FrameBufferBrdf;
FrameBuffer    Graphic::FrameBufferImage;