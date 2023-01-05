#pragma once
#include <glm/glm.hpp>
#include "Wismut/Renderer/VertexArray.h"

namespace Wi
{
	enum class RendererAPIType
	{
		None,
		OpenGL	
	};

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;
		virtual void Clear(glm::vec4 color) const = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const = 0;
		virtual void Init() = 0;
		virtual void SetViewport(int width, int height) = 0;

		static RendererAPIType GetAPI() { return s_CurrentAPI; }
		static Scope<RendererAPI> Create();

	private:
		inline static RendererAPIType s_CurrentAPI = RendererAPIType::OpenGL;
	};
}
