#pragma  once

#include "Graphic.h"

unsigned int Graphic::viewport_width;
unsigned int Graphic::viewport_height;

ConstantBuffer Graphic::ConstBufferCamera;
ConstantBuffer Graphic::ConstBufferModel;
ConstantBuffer Graphic::ConstBufferMaterial;
ConstantBuffer Graphic::ConstBufferLight;
ConstantBuffer Graphic::ConstBufferSkybox;
ConstantBuffer Graphic::ConstBufferCubeMap;
ConstantBuffer Graphic::ConstBufferAnimationBone;

FrameBuffer    Graphic::FrameBufferShadowMaps[NUM_MAX_POINT_LIGHT];
FrameBuffer    Graphic::FrameBufferCubeMap;
FrameBuffer    Graphic::FrameBufferIrradiance;
FrameBuffer    Graphic::FrameBufferSpecular;
FrameBuffer    Graphic::FrameBufferBrdf;
FrameBuffer    Graphic::FrameBufferImage;