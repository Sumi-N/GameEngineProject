#pragma  once

#include "Graphic.h"

ConstantBuffer Graphic::buffer_camera;
ConstantBuffer Graphic::buffer_ambientlight;
ConstantBuffer Graphic::buffer_pointlight;
ConstantBuffer Graphic::buffer_directionallight;
ConstantBuffer Graphic::buffer_model;
ConstantBuffer Graphic::buffer_material;

//int main()
//{
//
//	HelloTriangleApplication app;
//
//	try
//	{
//		app.run();
//	}
//	catch (const std::exception & e)
//	{
//		std::cerr << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//
//	return EXIT_SUCCESS;
//}