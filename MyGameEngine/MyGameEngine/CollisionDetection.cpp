#include "CollisionDetection.h"
#include "Matrix4.h"

#include <math.h>

/*
 ef == end time of the frame
 cf == current time of the frame
 rf == remain time in frame

 base  == the cordination which is based on the base object cordination  
 trans == the cordination which is trans to the base object cordination
*/

void Engine::CollisionDetection::Update(const float i_dt, Physics3D * i_phyA, Physics3D * i_phyB)
{
	Collision2D(0, i_dt, i_phyA,i_phyB);
}

void Engine::CollisionDetection::Collision2D(const float i_ddt, const float i_dt, Physics3D * i_phyA, Physics3D * i_phyB)
{
	Boundary bounA_cf;
	Boundary bounA_ef;
	Boundary bounB_cf;
	Boundary bounB_ef;

	// Update boundary information
	UpdateBoundary(i_ddt, i_dt, i_phyA, bounA_cf, bounA_ef);
	UpdateBoundary(i_ddt, i_dt, i_phyB, bounB_cf, bounB_ef);

	// Tranlate the one's cordination to the base object's cordination
	CordinationTranslation(i_ddt, i_dt, i_phyA, bounB_cf, bounB_ef);
	CordinationTranslation(i_ddt, i_dt, i_phyB, bounA_cf, bounA_ef);

	Vector2D<float, float> minmax_X_AinB_cf;
	Vector2D<float, float> minmax_X_AinB_ef;
	Vector2D<float, float> minmax_Y_AinB_cf;
	Vector2D<float, float> minmax_Y_AinB_ef;

	
	Vector2D<float, float> minmax_X_BinA_cf;
	Vector2D<float, float> minmax_X_BinA_ef;
	Vector2D<float, float> minmax_Y_BinA_cf;
	Vector2D<float, float> minmax_Y_BinA_ef;

	CastToAxis(X, bounA_cf, bounA_ef, minmax_X_AinB_cf, minmax_X_AinB_ef);
	CastToAxis(Y, bounA_cf, bounA_ef, minmax_Y_AinB_cf, minmax_Y_AinB_ef);
	CastToAxis(X, bounB_cf, bounB_ef, minmax_X_BinA_cf, minmax_X_BinA_ef);
	CastToAxis(Y, bounB_cf, bounB_ef, minmax_Y_BinA_cf, minmax_Y_BinA_ef);

	Vector2D<float, float> minmax_X_AinA = Vector2D<float,float>(-1 * i_phyA->pointer->extent_width.x, i_phyA->pointer->extent_width.x);
	Vector2D<float, float> minmax_Y_AinA = Vector2D<float, float>(-1 * i_phyA->pointer->extent_height.y, i_phyA->pointer->extent_height.y);

	Vector2D<float, float> minmax_X_BinB = Vector2D<float, float>(-1 * i_phyB->pointer->extent_width.x, i_phyB->pointer->extent_width.x);
	Vector2D<float, float> minmax_Y_BinB = Vector2D<float, float>(-1 * i_phyB->pointer->extent_height.y, i_phyB->pointer->extent_height.y);

	// Collision Detection
	if (CheckOverlapping(minmax_X_AinA, minmax_X_BinA_cf, minmax_X_BinA_ef)) {
		if (CheckOverlapping(minmax_Y_AinA, minmax_Y_BinA_cf, minmax_Y_BinA_ef)) {
			if (CheckOverlapping(minmax_X_BinB, minmax_X_AinB_cf, minmax_X_AinB_ef)) {
				if (CheckOverlapping(minmax_Y_BinB, minmax_Y_AinB_cf, minmax_Y_AinB_ef)) {
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
void Engine::CollisionDetection::UpdateBoundary(const float i_ddt, const float i_dt,Physics3D * i_phy, Boundary & o_boun_cf, Boundary & o_boun_ef)
{
	Vector3D center_initial = i_phy->pointer->pos + i_phy->pointer->extent_height;

	Vector3D center_cf = center_initial + i_ddt * i_phy->vel;
	Vector3D center_ef = center_initial + i_dt * i_phy->vel;

	Vector3D width = i_phy->pointer->extent_width;
	Vector3D height = i_phy->pointer->extent_height;

	o_boun_cf.ur = center_cf +  1 * width +  1 * height;
	o_boun_cf.ul = center_cf + -1 * width +  1 * height;
	o_boun_cf.lr = center_cf +  1 * width + -1 * height;
	o_boun_cf.ll = center_cf + -1 * width + -1 * height;

	o_boun_ef.ur = center_ef +  1 * width +  1 * height;
	o_boun_ef.ul = center_ef + -1 * width +  1 * height;
	o_boun_ef.lr = center_ef +  1 * width + -1 * height;
	o_boun_ef.ll = center_ef + -1 * width + -1 * height;

	return;
}

void Engine::CollisionDetection::CordinationTranslation(const float i_ddt, const float i_dt,Physics3D * i_phy_base, Boundary & o_boun_trans_cf, Boundary & o_boun_trans_ef)
{
	Engine::OwningPointer<Object3D> * obj_base = &(i_phy_base->pointer);

	float rotation_angle_cf    = -1 * ((*obj_base)->rot.z);
	float rotation_angle_ef = -1 * ((*obj_base)->rot.z); // This line should be changed onece the rotation update function ih physics3d has done.

	o_boun_trans_cf.ur = Matrix4::Yaw(rotation_angle_cf) * o_boun_trans_cf.ur;
	o_boun_trans_cf.ul = Matrix4::Yaw(rotation_angle_cf) * o_boun_trans_cf.ul;
	o_boun_trans_cf.lr = Matrix4::Yaw(rotation_angle_cf) * o_boun_trans_cf.lr;
	o_boun_trans_cf.ll = Matrix4::Yaw(rotation_angle_cf) * o_boun_trans_cf.ll;

	o_boun_trans_ef.ur = Matrix4::Yaw(rotation_angle_ef) * o_boun_trans_ef.ur;
	o_boun_trans_ef.ul = Matrix4::Yaw(rotation_angle_ef) * o_boun_trans_ef.ul;
	o_boun_trans_ef.lr = Matrix4::Yaw(rotation_angle_ef) * o_boun_trans_ef.lr;
	o_boun_trans_ef.ll = Matrix4::Yaw(rotation_angle_ef) * o_boun_trans_ef.ll;

	Vector3D base_center_initial = (*obj_base)->pos + (*obj_base)->extent_height;
	Vector3D base_center_cf = base_center_initial + i_ddt * i_phy_base->vel;
	Vector3D base_center_ef = base_center_initial + i_dt * i_phy_base->vel;

	o_boun_trans_cf.ur = o_boun_trans_cf.ur - base_center_cf;
	o_boun_trans_cf.ul = o_boun_trans_cf.ul - base_center_cf;
	o_boun_trans_cf.lr = o_boun_trans_cf.lr - base_center_cf;
	o_boun_trans_cf.ll = o_boun_trans_cf.ll - base_center_cf;

	o_boun_trans_ef.ur = o_boun_trans_ef.ur - base_center_ef;
	o_boun_trans_ef.ul = o_boun_trans_ef.ul - base_center_ef;
	o_boun_trans_ef.lr = o_boun_trans_ef.lr - base_center_ef;
	o_boun_trans_ef.ll = o_boun_trans_ef.ll - base_center_ef;
}

void Engine::CollisionDetection::CastToAxis(Axis axis, Boundary & i_boun_cf, Boundary & i_boun_ef, Vector2D<float, float>& minmax_cf, Vector2D<float, float>& minmax_ef)
{
	switch (axis) {
	case Axis::X :
		GetMinMax(minmax_cf,i_boun_cf.ur.x, i_boun_cf.ul.x, i_boun_cf.lr.x, i_boun_cf.ll.x);
		GetMinMax(minmax_ef, i_boun_ef.ur.x, i_boun_ef.ul.x, i_boun_ef.lr.x, i_boun_ef.ll.x);
		break;
	case Axis::Y :
		GetMinMax(minmax_cf, i_boun_cf.ur.y, i_boun_cf.ul.y, i_boun_cf.lr.y, i_boun_cf.ll.y);
		GetMinMax(minmax_ef, i_boun_ef.ur.y, i_boun_ef.ul.y, i_boun_ef.lr.y, i_boun_ef.ll.y);
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

bool Engine::CollisionDetection::CheckOverlapping(Vector2D<float, float> minmax_base, Vector2D<float, float> minmax_trans_cf, Vector2D<float, float> minmax_trans_ef)
{
	if ((minmax_base.x <= minmax_trans_ef.x && minmax_trans_ef.x <= minmax_base.y) || (minmax_base.x <= minmax_trans_ef.y && minmax_trans_ef.y <= minmax_base.y))
		return true;
	else if (((minmax_trans_cf.y < minmax_base.x) && (minmax_trans_ef.x > minmax_base.y)) || ((minmax_trans_cf.x > minmax_base.y) && (minmax_trans_ef.y < minmax_base.x)))
		return true;
	return false;
}

float Engine::CollisionDetection::CalculateCollisionTiming(const float rf, Vector2D<float, float> base, Vector2D<float, float> trans_cf, Vector2D<float, float> trans_ef)
{
	float distance_cf = fabsf(base.x - trans_cf.y) < fabsf(base.y - trans_cf.x) ? fabsf(base.x - trans_cf.y) : fabsf(base.y - trans_cf.x);
	float distance_ef = fabsf(base.x - trans_ef.y) < fabsf(base.y - trans_ef.x) ? fabsf(base.x - trans_ef.y) : fabsf(base.y - trans_ef.x);
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
//Boundary Engine::CollisionDetection::TranslateToLocal(Physics3D * i_base, Physics3D *  i_trans)
//{
//	Engine::OwningPointer<Object3D> * obj_base = &(i_base->pointer);
//	Engine::OwningPointer<Object3D> * obj_trans = &(i_trans->pointer);
//
//	Boundary boundary_trans = (*obj_trans)->boundary;
//
//	float rotation_angle = -1 * ((*obj_base)->rot.z + (*obj_trans)->rot.z);
//
//	boundary_trans.ur = Matrix4::Yaw(rotation_angle) * boundary_trans.ur;
//	boundary_trans.ul = Matrix4::Yaw(rotation_angle) * boundary_trans.ul;
//	boundary_trans.lr = Matrix4::Yaw(rotation_angle) * boundary_trans.lr;
//	boundary_trans.ll = Matrix4::Yaw(rotation_angle) * boundary_trans.ll;
//
//	boundary_trans.ur = boundary_trans.ur - ((*obj_base)->extent_height + (*obj_base)->pos);
//	boundary_trans.ul = boundary_trans.ul - ((*obj_base)->extent_height + (*obj_base)->pos);
//	boundary_trans.lr = boundary_trans.lr - ((*obj_base)->extent_height + (*obj_base)->pos);
//	boundary_trans.ll = boundary_trans.ll - ((*obj_base)->extent_height + (*obj_base)->pos);
//
//	return boundary_trans;
//}
//
//bool Engine::CollisionDetection::CastToXAxis(Physics3D * i_phy, Boundary i_boun)
//{
//	Vector2D<float, float> minmax_base;
//	Vector2D<float, float> minmax_trans;
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
//	minmax_trans.x = tmpmin;
//	minmax_trans.y = tmpmax;
//
//	if ((minmax_base.x <= minmax_trans.x && minmax_trans.x <= minmax_base.y) || (minmax_base.x <= minmax_trans.y && minmax_trans.y <= minmax_base.y))
//		return true;
//	else
//		return false;
//}
//
//bool Engine::CollisionDetection::CastToYAxis(Physics3D * i_phy, Boundary i_boun)
//{
//	Vector2D<float, float> minmax_base;
//	Vector2D<float, float> minmax_trans;
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
//	minmax_trans.x = tmpmin;
//	minmax_trans.y = tmpmax;
//
//	if ((minmax_base.x <= minmax_trans.x && minmax_trans.x <= minmax_base.y) || (minmax_base.x <= minmax_trans.y && minmax_trans.y <= minmax_base.y))
//		return true;
//	else
//		return false;
//}