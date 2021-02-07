#pragma  once

#include "pch.h"
#include "CppUnitTest.h"

#include <Core/Math/Vector.h>
#include <stdlib.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathUnitTest
{
	TEST_CLASS(MathUnitTest)
	{
	public:
		
		TEST_METHOD(VectorOffIntrinsicTest)
		{
			//for (int i = 0; i < INT_MAX; i++)
			for (int i = 0; i < 500000000; i++)
			{
				//Vec3f vec1 = Vec3f(rand() % 100, rand () %100, rand() % 100);
				//Vec3f vec2 = Vec3f(rand() % 100, rand() % 100, rand() % 100);

				Vec3f vec1 = Vec3f((static_cast<float>(rand()) / (RAND_MAX)), 2.1f, 2.3f);
				Vec3f vec2 = Vec3f(1.5f, 1.3f, 0.5f);

				Vec3f Vec3 = vec1 + vec2;
			}
		}

		//TEST_METHOD(VectorOnIntrinsicTest)
		//{
		//	//for (int i = 0; i < INT_MAX; i++)
		//	for (int i = 0; i < 100000000; i++)
		//	{
		//		//Vec3f vec1 = Vec3f(rand() % 100, rand () %100, rand() % 100);
		//		//Vec3f vec2 = Vec3f(rand() % 100, rand() % 100, rand() % 100);

		//		Vec3f vec1 = Vec3f((static_cast<float>(rand()) / (RAND_MAX)), 2.1f, 2.3f);
		//		Vec3f vec2 = Vec3f(1.5f, 1.3f, 0.5f);

		//		Vec3f Vec3 = vec1 + vec2;
		//	}
		//}
	};
}
