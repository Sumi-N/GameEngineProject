#pragma once

#include "Define.h"
#include "Thread.h"
#include "GameThread.h"

#ifdef ENGINE_GRAPHIC_OPENGL
	#include "Input.OpenGL.h"
#endif // ENGINE_GRAPHIC_OPENGL

class RenderThread : public Thread
{
public:
	void Boot() override;
	void Init() override;
	void Run() override;
	void Refresh();
	void CleanUp() override;
	void PassDataTo(Thread *) override;
};

inline void RenderThread::Boot()
{
	Graphic::Boot();

#ifdef ENGINE_GRAPHIC_OPENGL
	// Set up callback
	glfwSetKeyCallback(Graphic::window, GLFW_INPUT::KeyCallback);
	glfwSetMouseButtonCallback(Graphic::window, GLFW_INPUT::MouseButtonCallback);
	glfwSetCursorPosCallback(Graphic::window, GLFW_INPUT::CursorPositionCallback);
#endif // ENGINE_GRAPHIC_OPENGL
	
}


inline void RenderThread::Init()
{
	SceneEntity::Init();
	Graphic::Init();
}

inline void RenderThread::Run()
{
	bool brunning = true;

	while (brunning)
	{
		// Critical Section
		{
			std::lock_guard<std::mutex> lock_guard(Mutex_Render);

			{
				std::swap(data_game_own, data_render_own);
				std::swap(input_update_list_game_own, input_update_list_render_own);
			}

			b_render_ready = true;
			Condition_Render.notify_one();
		}

		if (!Graphic::PreUpdate())
		{
			brunning = false;
		}

		Graphic::Update(data_render_own);

		Graphic::PostUpdate(data_render_own);
	}
}

inline void RenderThread::CleanUp()
{

}

inline void RenderThread::PassDataTo(Thread * i_thread)
{

}