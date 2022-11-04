#include "wipch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Wismut/Core/Assert.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			Context::Context(GLFWwindow* window)
				: m_Window(window)
			{
			}

			void Context::Init()
			{
				glfwMakeContextCurrent(m_Window);
				int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
				WI_CORE_ASSERT(status, "Failed to load glad");

				WI_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
				WI_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
				WI_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
			}

			void Context::SwapBuffers()
			{
				glfwSwapBuffers(m_Window);
			}
		}
	}
}
