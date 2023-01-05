#include "wipch.h"
#include "Wismut/Platform/OpenGL/OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Wi
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		WI_CORE_ASSERT(status, "Failed to load glad");

		WI_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		WI_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		WI_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}
}
