#pragma  once

#include "Graphic.h"

ConstantBuffer Graphic::buffer_camera;
ConstantBuffer Graphic::buffer_light;


//int Graphic::Vulkan::testThread()
//{
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
//	return EXIT_SUCCESS;;
//}

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