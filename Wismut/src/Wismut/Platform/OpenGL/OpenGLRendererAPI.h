#pragma once
#include "Wismut/Renderer/RendererAPI.h"

namespace Wi
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Clear(glm::vec4 color) const override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const override;
	};
}
