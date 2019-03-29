#include "CollisionDetection.h"
#include "Matrix4.h"

void Engine::CollisionDetection::Update(const float dt, Physics3D * i_phyA, Physics3D * i_phyB)
{
	For2D(dt, i_phyA,i_phyB);
}

void Engine::CollisionDetection::For2D(const float dt, Physics3D * i_phyA, Physics3D * i_phyB)
{
	// Update boundary information
	i_phyA->pointer->updateBoundary();
	i_phyB->pointer->updateBoundary();

	// Collision Detection
	Boundary bina = TranslateToLocal(i_phyA, i_phyB);
	Boundary ainb = TranslateToLocal(i_phyB, i_phyA);
	if (CastToXAxis(i_phyA, bina)) {
		if (CastToYAxis(i_phyA, bina)) {
			if (CastToXAxis(i_phyB, ainb)) {
				if (CastToYAxis(i_phyB, ainb)) {
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

Boundary Engine::CollisionDetection::TranslateToLocal(Physics3D * i_base, Physics3D *  i_translated)
{
	Engine::OwningPointer<Object3D> * obj_base = &(i_base->pointer);
	Engine::OwningPointer<Object3D> * obj_translated = &(i_translated->pointer);

	Boundary boundary_translated = (*obj_translated)->boundary;

	float rotation_angle = -1 * ((*obj_base)->rot.z + (*obj_translated)->rot.z);

	boundary_translated.ur = Matrix4::Yaw(rotation_angle) * boundary_translated.ur;
	boundary_translated.ul = Matrix4::Yaw(rotation_angle) * boundary_translated.ul;
	boundary_translated.lr = Matrix4::Yaw(rotation_angle) * boundary_translated.lr;
	boundary_translated.ll = Matrix4::Yaw(rotation_angle) * boundary_translated.ll;

	boundary_translated.ur = boundary_translated.ur - ((*obj_base)->aabb.extent_height + (*obj_base)->pos);
	boundary_translated.ul = boundary_translated.ul - ((*obj_base)->aabb.extent_height + (*obj_base)->pos);
	boundary_translated.lr = boundary_translated.lr - ((*obj_base)->aabb.extent_height + (*obj_base)->pos);
	boundary_translated.ll = boundary_translated.ll - ((*obj_base)->aabb.extent_height + (*obj_base)->pos);

	return boundary_translated;
}

void Engine::CollisionDetection::CordinationTranslation(const float dt, Physics3D * phy_base, Physics3D * phy_translated, Boundary & translated_before, Boundary & translated_after)
{
	Engine::OwningPointer<Object3D> * obj_base = &(phy_base->pointer);
	Engine::OwningPointer<Object3D> * obj_translated = &(phy_translated->pointer);
}

void Engine::CollisionDetection::CastToAxis(Axis, Physics3D *, Physics3D *, Vector2D<float, float>&, Vector2D<float, float>&)
{
}

bool Engine::CollisionDetection::CastToXAxis(Physics3D * i_phy, Boundary i_boun)
{
	Vector2D<float, float> minmax_base;
	Vector2D<float, float> minmax_tralslated;

	minmax_base.x = -1 * (i_phy->pointer->aabb.extent_width.x);
	minmax_base.y = (i_phy->pointer->aabb.extent_width.x);

	float tmpmin = i_boun.ur.x < i_boun.ul.x ? i_boun.ur.x : i_boun.ul.x;
	tmpmin = tmpmin < i_boun.lr.x ? tmpmin : i_boun.lr.x;
	tmpmin = tmpmin < i_boun.ll.x ? tmpmin : i_boun.ll.x;

	float tmpmax = i_boun.ur.x > i_boun.ul.x ? i_boun.ur.x : i_boun.ul.x;
	tmpmax = tmpmax > i_boun.lr.x ? tmpmax : i_boun.lr.x;
	tmpmax = tmpmax > i_boun.ll.x ? tmpmax : i_boun.ll.x;

	minmax_tralslated.x = tmpmin;
	minmax_tralslated.y = tmpmax;

	if ((minmax_base.x <= minmax_tralslated.x && minmax_tralslated.x <= minmax_base.y) || (minmax_base.x <= minmax_tralslated.y && minmax_tralslated.y <= minmax_base.y))
		return true;
	else
		return false;
}

bool Engine::CollisionDetection::CastToYAxis(Physics3D * i_phy, Boundary i_boun)
{
	Vector2D<float, float> minmax_base;
	Vector2D<float, float> minmax_tralslated;

	minmax_base.x = -1 * (i_phy->pointer->aabb.extent_height.y);
	minmax_base.y = (i_phy->pointer->aabb.extent_height.y);

	float tmpmin = i_boun.ur.y < i_boun.ul.y ? i_boun.ur.y : i_boun.ul.y;
	tmpmin = tmpmin < i_boun.lr.y ? tmpmin : i_boun.lr.y;
	tmpmin = tmpmin < i_boun.ll.y ? tmpmin : i_boun.ll.y;

	float tmpmax = i_boun.ur.y > i_boun.ul.y ? i_boun.ur.y : i_boun.ul.y;
	tmpmax = tmpmax > i_boun.lr.y ? tmpmax : i_boun.lr.y;
	tmpmax = tmpmax > i_boun.ll.y ? tmpmax : i_boun.ll.y;

	minmax_tralslated.x = tmpmin;
	minmax_tralslated.y = tmpmax;

	if ((minmax_base.x <= minmax_tralslated.x && minmax_tralslated.x <= minmax_base.y) || (minmax_base.x <= minmax_tralslated.y && minmax_tralslated.y <= minmax_base.y))
		return true;
	else
		return false;
}

bool Engine::CollisionDetection::CompareMinMax(const float, Vector2D<float, float>, Vector2D<float, float>, Vector2D<float, float>, Vector2D<float, float>)
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
