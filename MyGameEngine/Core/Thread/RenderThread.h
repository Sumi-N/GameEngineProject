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
	void CleanUp() override;
	void PassDataTo(Thread *) override;
};

inline void RenderThread::Boot()
{
	Graphic::Init();

#ifdef ENGINE_GRAPHIC_OPENGL
	// Set up callback
	glfwSetKeyCallback(Graphic::window, GLFW_INPUT::KeyCallback);
	glfwSetMouseButtonCallback(Graphic::window, GLFW_INPUT::MouseButtonCallback);
	glfwSetCursorPosCallback(Graphic::window, GLFW_INPUT::CursorPositionCallback);
#endif // ENGINE_GRAPHIC_OPENGL
	
}


inline void RenderThread::Init()
{
	Graphic::PostInit();

	input_render_own->Init();
	//input_render_own->Init();
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
				//std::swap(input_game_own, input_render_own);
			}

			b_render_ready = true;
			Condition_Render.notify_one();
		}

		// Cleanup input info
		input_render_own->Clear();

		if (!Graphic::PreUpdate())
		{
			brunning = false;
		}

		Graphic::Update(data_render_own);

		Graphic::PostUpdate();

		// Cleanup section
		data_render_own->model_data.clear();
	}
}

inline void RenderThread::CleanUp()
{

}

inline void RenderThread::PassDataTo(Thread * i_thread)
{

}