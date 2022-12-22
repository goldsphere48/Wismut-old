#pragma once
#include "Wismut/Renderer/RendererAPI.h"

namespace Wi
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Clear(glm::vec4 color) const override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) const override;
		void SetViewport(int width, int height) override;
	};
}
