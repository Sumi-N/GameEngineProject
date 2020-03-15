#pragma once

#include "Define.h"
#include "Thread.h"

//Data required for render thread
GraphicRequiredData  container_render[2];
GraphicRequiredData* data_game_own = &container_render[0];
GraphicRequiredData* data_render_own = &container_render[1];

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
}


inline void RenderThread::Init()
{
	Graphic::PostInit();
}

inline void RenderThread::Run()
{
	while (true)
	{
		// Critical Section
		{
			std::lock_guard<std::mutex> lock_guard(Mutex_Render);

			{
				std::swap(data_game_own, data_render_own);
			}

			b_render_ready = true;
			Condition_Render.notify_one();
		}

		Graphic::PreUpdate();

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