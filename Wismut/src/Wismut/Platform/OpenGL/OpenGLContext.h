#pragma once
#include "Wismut/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Wi
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}