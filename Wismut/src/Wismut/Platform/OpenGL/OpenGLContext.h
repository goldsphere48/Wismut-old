#pragma once
#include "Wismut/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Wi
{
	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;

	private:
		GLFWwindow* m_Window;
	};
}