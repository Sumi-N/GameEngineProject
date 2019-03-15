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
		hi.show();
		hi.inversion();
		hi.show();
		hi.tranpose();
		hi.show();
	}
}