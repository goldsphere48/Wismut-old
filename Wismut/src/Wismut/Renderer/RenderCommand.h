#pragma once
#include "RendererAPI.h"

namespace Wi
{
	class RenderCommand
	{
	public:
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		static void Clear(glm::vec4 color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
		{
			s_RendererAPI->Clear(color);
		}

	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};
}
