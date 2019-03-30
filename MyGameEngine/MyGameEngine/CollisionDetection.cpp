#include "CollisionDetection.h"
#include "Matrix4.h"

void Engine::CollisionDetection::Update(const float i_dt, Physics3D * i_phyA, Physics3D * i_phyB)
{
	Collision2D(0, i_dt, i_phyA,i_phyB);
}

void Engine::CollisionDetection::Collision2D(const float i_ddt, const float i_dt, Physics3D * i_phyA, Physics3D * i_phyB)
{
	Boundary bounA_now;
	Boundary bounA_future;
	Boundary bounB_now;
	Boundary bounB_future;

	// Update boundary information
	UpdateBoundary(i_ddt, i_dt, i_phyA, bounA_now, bounA_future);
	UpdateBoundary(i_ddt, i_dt, i_phyB, bounB_now, bounB_future);

	// Tranlate the one's cordination to the base object's cordination
	CordinationTranslation(i_ddt, i_dt, i_phyA, bounB_now, bounB_future);
	CordinationTranslation(i_ddt, i_dt, i_phyB, bounA_now, bounA_future);

	Vector2D<float, float> minmax_X_AinB_now;
	Vector2D<float, float> minmax_X_AinB_future;
	Vector2D<float, float> minmax_Y_AinB_now;
	Vector2D<float, float> minmax_Y_AinB_future;

	
	Vector2D<float, float> minmax_X_BinA_now;
	Vector2D<float, float> minmax_X_BinA_future;
	Vector2D<float, float> minmax_Y_BinA_now;
	Vector2D<float, float> minmax_Y_BinA_future;

	CastToAxis(X, bounA_now, bounA_future, minmax_X_AinB_now, minmax_X_AinB_future);
	CastToAxis(Y, bounA_now, bounA_future, minmax_Y_AinB_now, minmax_Y_AinB_future);
	CastToAxis(X, bounB_now, bounB_future, minmax_X_BinA_now, minmax_X_BinA_future);
	CastToAxis(Y, bounB_now, bounB_future, minmax_Y_BinA_now, minmax_Y_BinA_future);

	Vector2D<float, float> minmax_X_AinA = Vector2D<float,float>(-1 * i_phyA->pointer->extent_width.x, i_phyA->pointer->extent_width.x);
	Vector2D<float, float> minmax_Y_AinA = Vector2D<float, float>(-1 * i_phyA->pointer->extent_height.y, i_phyA->pointer->extent_height.y);

	Vector2D<float, float> minmax_X_BinB = Vector2D<float, float>(-1 * i_phyB->pointer->extent_width.x, i_phyB->pointer->extent_width.x);
	Vector2D<float, float> minmax_Y_BinB = Vector2D<float, float>(-1 * i_phyB->pointer->extent_height.y, i_phyB->pointer->extent_height.y);

	// Collision Detection
	if (CheckOverlapping(minmax_X_AinA, minmax_X_BinA_future)) {
		if (CheckOverlapping(minmax_Y_AinA, minmax_Y_BinA_future)) {
			if (CheckOverlapping(minmax_X_BinB, minmax_X_AinB_future)) {
				if (CheckOverlapping(minmax_Y_BinB, minmax_Y_AinB_future)) {
					DEBUG_PRINT("IT'S COLLIGIND!!!!");
					Collide(i_phyA, i_phyB);
					return;
				}
				else {
					//DEBUG_PRINT("Nop4");
					return;
				}
			}
			else {
				//DEBUG_PRINT("Nop3");
				return;
			}
		}
		else {
			//DEBUG_PRINT("Nop2");
			return;
		}
	}
	else {
		//DEBUG_PRINT("Nop1");
		return;
	}
}

// This update boundary function doesn't consider the rotation of the object for reducing the additional calculation in the later part of collision detection;
void Engine::CollisionDetection::UpdateBoundary(const float i_ddt, const float i_dt,Physics3D * i_phy, Boundary & o_boun_now, Boundary & o_boun_future)
{
	Vector3D center_initial = i_phy->pointer->pos + i_phy->pointer->extent_height;

	Vector3D center_now = center_initial + i_ddt * i_phy->vel;
	Vector3D center_future = center_initial + i_dt * i_phy->vel;

	Vector3D width = i_phy->pointer->extent_width;
	Vector3D height = i_phy->pointer->extent_height;

	o_boun_now.ur = center_now +  1 * width +  1 * height;
	o_boun_now.ul = center_now + -1 * width +  1 * height;
	o_boun_now.lr = center_now +  1 * width + -1 * height;
	o_boun_now.ll = center_now + -1 * width + -1 * height;

	o_boun_future.ur = center_future +  1 * width +  1 * height;
	o_boun_future.ul = center_future + -1 * width +  1 * height;
	o_boun_future.lr = center_future +  1 * width + -1 * height;
	o_boun_future.ll = center_future + -1 * width + -1 * height;

	return;
}

void Engine::CollisionDetection::CordinationTranslation(const float i_ddt, const float i_dt,Physics3D * i_phy_base, Boundary & o_boun_translated_now, Boundary & o_boun_translated_future)
{
	Engine::OwningPointer<Object3D> * obj_base = &(i_phy_base->pointer);

	float rotation_angle_now    = -1 * ((*obj_base)->rot.z);
	float rotation_angle_future = -1 * ((*obj_base)->rot.z); // This line should be changed onece the rotation update function ih physics3d has done.

	o_boun_translated_now.ur = Matrix4::Yaw(rotation_angle_now) * o_boun_translated_now.ur;
	o_boun_translated_now.ul = Matrix4::Yaw(rotation_angle_now) * o_boun_translated_now.ul;
	o_boun_translated_now.lr = Matrix4::Yaw(rotation_angle_now) * o_boun_translated_now.lr;
	o_boun_translated_now.ll = Matrix4::Yaw(rotation_angle_now) * o_boun_translated_now.ll;

	o_boun_translated_future.ur = Matrix4::Yaw(rotation_angle_future) * o_boun_translated_future.ur;
	o_boun_translated_future.ul = Matrix4::Yaw(rotation_angle_future) * o_boun_translated_future.ul;
	o_boun_translated_future.lr = Matrix4::Yaw(rotation_angle_future) * o_boun_translated_future.lr;
	o_boun_translated_future.ll = Matrix4::Yaw(rotation_angle_future) * o_boun_translated_future.ll;

	Vector3D base_center_initial = (*obj_base)->pos + (*obj_base)->extent_height;
	Vector3D base_center_now = base_center_initial + i_ddt * i_phy_base->vel;
	Vector3D base_center_future = base_center_initial + i_dt * i_phy_base->vel;

	o_boun_translated_now.ur = o_boun_translated_now.ur - base_center_now;
	o_boun_translated_now.ul = o_boun_translated_now.ul - base_center_now;
	o_boun_translated_now.lr = o_boun_translated_now.lr - base_center_now;
	o_boun_translated_now.ll = o_boun_translated_now.ll - base_center_now;

	o_boun_translated_future.ur = o_boun_translated_future.ur - base_center_future;
	o_boun_translated_future.ul = o_boun_translated_future.ul - base_center_future;
	o_boun_translated_future.lr = o_boun_translated_future.lr - base_center_future;
	o_boun_translated_future.ll = o_boun_translated_future.ll - base_center_future;
}

void Engine::CollisionDetection::CastToAxis(Axis axis, Boundary & i_boun_now, Boundary & i_boun_future, Vector2D<float, float>& minmax_now, Vector2D<float, float>& minmax_future)
{
	switch (axis) {
	case Axis::X :
		GetMinMax(minmax_now,i_boun_now.ur.x, i_boun_now.ul.x, i_boun_now.lr.x, i_boun_now.ll.x);
		GetMinMax(minmax_future, i_boun_future.ur.x, i_boun_future.ul.x, i_boun_future.lr.x, i_boun_future.ll.x);
		break;
	case Axis::Y :
		GetMinMax(minmax_now, i_boun_now.ur.y, i_boun_now.ul.y, i_boun_now.lr.y, i_boun_now.ll.y);
		GetMinMax(minmax_future, i_boun_future.ur.y, i_boun_future.ul.y, i_boun_future.lr.y, i_boun_future.ll.y);
		break;
	case Axis::Z :
		break;
	}
}

void Engine::CollisionDetection::GetMinMax(Vector2D<float, float> & o_minmax, float ur, float ul, float lr, float ll)
{
	float tmpmin = ur < ul ? ur : ul;
	tmpmin = tmpmin < lr ? tmpmin : lr;
	tmpmin = tmpmin < ll ? tmpmin : ll;

	float tmpmax = ur > ul ? ur : ul;
	tmpmax = tmpmax > lr ? tmpmax : lr;
	tmpmax = tmpmax > ll ? tmpmax : ll;

	o_minmax.x = tmpmin;
	o_minmax.y = tmpmax;

	return;
}

bool Engine::CollisionDetection::CheckOverlapping(Vector2D<float, float> minmax1, Vector2D<float, float> minmax2)
{
	if ((minmax1.x <= minmax2.x && minmax2.x <= minmax1.y) || (minmax1.x <= minmax2.y && minmax2.y <= minmax1.y))
		return true;
	return false;
}

float Engine::CollisionDetection::CalculateCollisionTiming(const float remain_t, Vector2D<float, float> base_now, Vector2D<float, float> base_future, Vector2D<float, float> translated_now, Vector2D<float, float> tranlated_future)
{
	return false;
}

void Engine::CollisionDetection::Collide(Physics3D * i_phyA, Physics3D * i_phyB)
{
	Vector3D tmp_vel_A = ((i_phyA->mass - i_phyB->mass) * i_phyA->vel + 2 * i_phyB->mass * i_phyB->vel) / (i_phyA->mass + i_phyB->mass);
	Vector3D tmp_vel_B = ((i_phyB->mass - i_phyA->mass) * i_phyB->vel + 2 * i_phyA->mass * i_phyA->vel) / (i_phyA->mass + i_phyB->mass);
	i_phyA->vel = tmp_vel_A;
	i_phyB->vel = tmp_vel_B;
}

//////////////// Legacy ///////////////////

//void Engine::CollisionDetection::For2D(const float i_dt, Physics3D * i_phyA, Physics3D * i_phyB)
//{
//	// Update boundary information
//	i_phyA->pointer->updateBoundary();
//	i_phyB->pointer->updateBoundary();
//
//	// Collision Detection
//	Boundary bina = TranslateToLocal(i_phyA, i_phyB);
//	Boundary ainb = TranslateToLocal(i_phyB, i_phyA);
//	if (CastToXAxis(i_phyA, bina)) {
//		if (CastToYAxis(i_phyA, bina)) {
//			if (CastToXAxis(i_phyB, ainb)) {
//				if (CastToYAxis(i_phyB, ainb)) {
//					DEBUG_PRINT("IT'S COLLIGIND!!!!");
//					Collide(i_phyA, i_phyB);
//					return;
//				}
//				else {
//					//DEBUG_PRINT("Nop4");
//					return;
//				}
//			}
//			else {
//				//DEBUG_PRINT("Nop3");
//				return;
//			}
//		}
//		else {
//			//DEBUG_PRINT("Nop2");
//			return;
//		}
//	}
//	else {
//		//DEBUG_PRINT("Nop1");
//		return;
//	}
//}
//
//Boundary Engine::CollisionDetection::TranslateToLocal(Physics3D * i_base, Physics3D *  i_translated)
//{
//	Engine::OwningPointer<Object3D> * obj_base = &(i_base->pointer);
//	Engine::OwningPointer<Object3D> * obj_translated = &(i_translated->pointer);
//
//	Boundary boundary_translated = (*obj_translated)->boundary;
//
//	float rotation_angle = -1 * ((*obj_base)->rot.z + (*obj_translated)->rot.z);
//
//	boundary_translated.ur = Matrix4::Yaw(rotation_angle) * boundary_translated.ur;
//	boundary_translated.ul = Matrix4::Yaw(rotation_angle) * boundary_translated.ul;
//	boundary_translated.lr = Matrix4::Yaw(rotation_angle) * boundary_translated.lr;
//	boundary_translated.ll = Matrix4::Yaw(rotation_angle) * boundary_translated.ll;
//
//	boundary_translated.ur = boundary_translated.ur - ((*obj_base)->extent_height + (*obj_base)->pos);
//	boundary_translated.ul = boundary_translated.ul - ((*obj_base)->extent_height + (*obj_base)->pos);
//	boundary_translated.lr = boundary_translated.lr - ((*obj_base)->extent_height + (*obj_base)->pos);
//	boundary_translated.ll = boundary_translated.ll - ((*obj_base)->extent_height + (*obj_base)->pos);
//
//	return boundary_translated;
//}
//
//bool Engine::CollisionDetection::CastToXAxis(Physics3D * i_phy, Boundary i_boun)
//{
//	Vector2D<float, float> minmax_base;
//	Vector2D<float, float> minmax_tralslated;
//
//	minmax_base.x = -1 * (i_phy->pointer->extent_width.x);
//	minmax_base.y = (i_phy->pointer->extent_width.x);
//
//	float tmpmin = i_boun.ur.x < i_boun.ul.x ? i_boun.ur.x : i_boun.ul.x;
//	tmpmin = tmpmin < i_boun.lr.x ? tmpmin : i_boun.lr.x;
//	tmpmin = tmpmin < i_boun.ll.x ? tmpmin : i_boun.ll.x;
//
//	float tmpmax = i_boun.ur.x > i_boun.ul.x ? i_boun.ur.x : i_boun.ul.x;
//	tmpmax = tmpmax > i_boun.lr.x ? tmpmax : i_boun.lr.x;
//	tmpmax = tmpmax > i_boun.ll.x ? tmpmax : i_boun.ll.x;
//
//	minmax_tralslated.x = tmpmin;
//	minmax_tralslated.y = tmpmax;
//
//	if ((minmax_base.x <= minmax_tralslated.x && minmax_tralslated.x <= minmax_base.y) || (minmax_base.x <= minmax_tralslated.y && minmax_tralslated.y <= minmax_base.y))
//		return true;
//	else
//		return false;
//}
//
//bool Engine::CollisionDetection::CastToYAxis(Physics3D * i_phy, Boundary i_boun)
//{
//	Vector2D<float, float> minmax_base;
//	Vector2D<float, float> minmax_tralslated;
//
//	minmax_base.x = -1 * (i_phy->pointer->extent_height.y);
//	minmax_base.y = (i_phy->pointer->extent_height.y);
//
//	float tmpmin = i_boun.ur.y < i_boun.ul.y ? i_boun.ur.y : i_boun.ul.y;
//	tmpmin = tmpmin < i_boun.lr.y ? tmpmin : i_boun.lr.y;
//	tmpmin = tmpmin < i_boun.ll.y ? tmpmin : i_boun.ll.y;
//
//	float tmpmax = i_boun.ur.y > i_boun.ul.y ? i_boun.ur.y : i_boun.ul.y;
//	tmpmax = tmpmax > i_boun.lr.y ? tmpmax : i_boun.lr.y;
//	tmpmax = tmpmax > i_boun.ll.y ? tmpmax : i_boun.ll.y;
//
//	minmax_tralslated.x = tmpmin;
//	minmax_tralslated.y = tmpmax;
//
//	if ((minmax_base.x <= minmax_tralslated.x && minmax_tralslated.x <= minmax_base.y) || (minmax_base.x <= minmax_tralslated.y && minmax_tralslated.y <= minmax_base.y))
//		return true;
//	else
//		return false;
//}