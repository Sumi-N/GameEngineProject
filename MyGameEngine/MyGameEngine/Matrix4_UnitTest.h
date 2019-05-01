#include "Matrix4.h"
#include "Vector4D.h"

namespace UnitTest {
	void MatrixUnitTest() {
		//float hello[16] = {1,0,0,0,
		//				   0,1,0,0,
		//				   0,0,1,0,
		//				   0,0,0,1};

		float hello[16] = { 2,4,1,2,
						    4,1,2,4,
						    5,6,7,2,
						    4,3,2,1 };

		Matrix4 hi = Matrix4(hello);
		//hi.show();
		hi.inversion();
		//hi.show();
		hi.tranpose();
		//hi.show();

		Matrix4 yoyoyo = Matrix4(hello);

		// float * Matrix4 
		yoyoyo = 5.0f * yoyoyo;
		yoyoyo.show();

		// Matrix4 / float
		yoyoyo = yoyoyo / 3.0;
		yoyoyo.show();

		// Matrix4 + Matrix4
		yoyoyo = yoyoyo + hi;
		yoyoyo.show();

		// Matrix4 - Matrix4
		yoyoyo = yoyoyo - hi;
		yoyoyo.show();
	}

//#define INTRIN
	void MatrixProfilingTest() {
		float randomFloats[16];
		for (int i = 0; i < 16; i++) {
			randomFloats[i] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5));
		}
		Matrix4 randomMatrix = Matrix4(randomFloats);
		Matrix4 result;

#if defined INTRIN
		randomMatrix.inverseSSE(result);
#else
		randomMatrix.inversion();
#endif
	}
}