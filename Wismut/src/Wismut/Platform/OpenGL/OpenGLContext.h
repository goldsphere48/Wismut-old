#pragma once

#include "Wismut/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			class Context : public Render::Context
			{
			public:
				Context(GLFWwindow* window);

				void Init() override;
				void SwapBuffers() override;

			private:
				GLFWwindow* m_Window;
			};
		}
	}
}