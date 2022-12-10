#pragma once
#include <glm/glm.hpp>
#include "Wismut/Renderer/VertexArray.h"

namespace Wi
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void Clear(glm::vec4 color) const = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const = 0;
		virtual void Init() = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();

	private:
		static API s_API;
	};
}
