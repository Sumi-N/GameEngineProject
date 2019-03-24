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
}