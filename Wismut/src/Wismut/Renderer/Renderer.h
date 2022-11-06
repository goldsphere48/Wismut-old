#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Wi
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}
