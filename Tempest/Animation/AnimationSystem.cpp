#include "Define.h"
#include "AnimationSystem.h"

namespace Tempest
{
	void AnimationSystem::Register(const OwningPointer<AnimationComponent>& i_animation)
	{
		list.PushBack(i_animation);
	}

	void AnimationSystem::Boot()
	{
		for (auto it = list.Begin(); it != list.End(); ++it)
		{
			(*it)->Boot();
		}
	}

	void AnimationSystem::Init()
	{
		for (auto it = list.Begin(); it != list.End(); ++it)
		{
			(*it)->Init();			
		}
	}

	void AnimationSystem::Update(float i_dt)
	{
		for (auto it = list.Begin(); it != list.End(); ++it)
		{
			(*it)->Update(i_dt);

			animation_current_time += i_dt;
			InterpolateMatrixBetweenFrames(*(*it)->clip, i_dt, animation_current_time, bones, true);
			
			for (int i = 0; i < (*it)->skeleton->joints.Size(); i++)
			{
				bones[i] = bones[i] * (*it)->skeleton->joints[i].inversed;
			}
		}
	}

	void AnimationSystem::CleanUp()
	{
		for (auto it = list.Begin(); it != list.End(); ++it)
		{
			(*it)->CleanUp();
		}
	}

	Result AnimationSystem::InterpolateMatrixBetweenFrames(const AnimationClip& i_clip, const float i_dt, float& i_total_passed_time, Mat4f* io_mat, const bool& i_isloop)
	{		
		int   num_frame_count = static_cast<int>(i_clip.samples.Size());
		float frame_per_count = 50;

		while (i_total_passed_time >= num_frame_count * frame_per_count)
		{
			i_total_passed_time -= num_frame_count * frame_per_count;
		}

		int current_frame = static_cast<int>(i_total_passed_time / frame_per_count);		
		
		if (current_frame == num_frame_count - 1)
		{
			if (!i_isloop)
			{
				return ResultValue::Failure;
			}
			else
			{
				// t is the ratio of passed time from the last frame in an animation
				float t = i_total_passed_time - current_frame * frame_per_count;
				t /= frame_per_count;
				t = 1 - t;

				for (int i = 0; i < i_clip.samples[0].jointposes.Size(); i++)
				{
					Vec4f pointA = i_clip.samples[current_frame].jointposes[i].trans;
					Vec4f pointB = i_clip.samples[0].jointposes[i].trans;

					Vec4f translation = t * pointA + (1 - t) * pointB;

					Quaternionf rotation = Quaternionf::Lerp(i_clip.samples[current_frame].jointposes[i].rot, i_clip.samples[0].jointposes[i].rot, 1 - t);
					rotation.Normalize();

					Mat4f rotation_matrix = Quaternionf::QuaternionToRotationMatix(rotation);
					Mat4f identity_matrix;
					io_mat[i] = identity_matrix.Translate(Vec3f(translation)) * rotation_matrix;
				}

				return ResultValue::Success;
			}
		}
		else
		{
			// t is the ratio of passed time from the last frame in an animation
			float t = i_total_passed_time - current_frame * frame_per_count;
			t /= frame_per_count;
			t = 1 - t;						

			for (int i = 0; i < i_clip.samples[0].jointposes.Size(); i++)
			{
				Vec4f pointA = i_clip.samples[current_frame].jointposes[i].trans;
				Vec4f pointB = i_clip.samples[current_frame + 1].jointposes[i].trans;

				Vec4f translation = t * pointA + (1 - t) * pointB;

				Quaternionf rotation = Quaternionf::Lerp(i_clip.samples[current_frame].jointposes[i].rot, i_clip.samples[current_frame + 1].jointposes[i].rot, 1 - t);
				rotation.Normalize();

				Mat4f rotation_matrix = Quaternionf::QuaternionToRotationMatix(rotation);
				Mat4f identity_matrix;
				io_mat[i] = identity_matrix.Translate(Vec3f(translation)) * rotation_matrix;
			}

			return ResultValue::Success;
		}
	}
}
