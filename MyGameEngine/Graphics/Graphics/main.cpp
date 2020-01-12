#include "Graphic_Vulkan.h"
#include <thread>

void testThread()
{
	//HelloTriangleApplication app;

	//try
	//{
	//	app.run();
	//}
	//catch (const std::exception & e)
	//{
	//	std::cerr << e.what() << std::endl;
	//	return;
	//}

	while (1)
	{
		//printf("hello world");
	}

	return;
}

int main()
{
	std::thread th1(testThread);
	th1.detach();

	HelloTriangleApplication app;

	try
	{
		app.run();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	//th1.join();

	return EXIT_SUCCESS;
}