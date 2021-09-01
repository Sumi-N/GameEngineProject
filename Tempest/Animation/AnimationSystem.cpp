#include "Define.h"
#include "AnimationSystem.h"


void AnimationSystem::Update()
{

}

Result AnimationSystem::InterpolateMatrixOfAFrame(const AnimationClip i_clip, const float i_total_passed_time, Mat4f* io_mat)
{
	int   num_frame_count = i_clip.frame_count;
	float frame_per_count = i_clip.frame_per_second;

	int current_frame = static_cast<int>((i_total_passed_time - frame_per_count) / frame_per_count);

	if (current_frame >= num_frame_count)
	{
		ResultValue::Failure;
	}
	else if (current_frame == num_frame_count - 1)
	{
		if (!i_clip.do_looping)
		{
			ResultValue::Failure;
		}
		else
		{
			// t is the ratio of passed time from the last frame in an animation
			float t = i_total_passed_time - (current_frame * frame_per_count);
			t /= frame_per_count;

			for (int i = 0; i < i_clip.samples[0].jointposes.Size(); i++)
			{
				Vec4f pointA = i_clip.samples[current_frame].jointposes[i].trans;
				Vec4f pointB = i_clip.samples[0].jointposes[i].trans;

				Vec4f translation = t * pointA + (1 - t) * pointB;
				
				Quaternionf rotation = t * i_clip.samples[current_frame].jointposes[i].rot + (1 - t) * i_clip.samples[0].jointposes[i].rot;
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
		float t = (current_frame + 1) * frame_per_count - i_total_passed_time;
		t /= frame_per_count;

		for (int i = 0; i < i_clip.samples[0].jointposes.Size(); i++)
		{
			Vec4f pointA = i_clip.samples[current_frame].jointposes[i].trans;
			Vec4f pointB = i_clip.samples[current_frame + 1].jointposes[i].trans;

			Vec4f translation = t * pointA + (1 - t) * pointB;
			
			Quaternionf rotation = t * i_clip.samples[current_frame].jointposes[i].rot + (1 - t) * i_clip.samples[current_frame + 1].jointposes[i].rot;
			rotation.Normalize();

			Mat4f rotation_matrix = Quaternionf::QuaternionToRotationMatix(rotation);
			Mat4f identity_matrix;
			io_mat[i] = identity_matrix.Translate(Vec3f(translation)) * rotation_matrix;
		}
	}
}
