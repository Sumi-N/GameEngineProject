#pragma once

namespace Tempest
{
	class RenderCommand
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit();
	};
}
