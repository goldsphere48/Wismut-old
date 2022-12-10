#include "wipch.h"
#include "Wismut/Platform/OpenGL/OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Wi
{
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message, const void* userParam)
	{
		if (severity == GL_DEBUG_SEVERITY_HIGH)
			WI_CORE_ERROR("OpenGL Error: Type: {0}, severity: {1}, message: {2}", type, severity, message);

		if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_LOW)
			WI_CORE_WARN("OpenGL Warning: Type: {0}, severity: {1}, message: {2}", type, severity, message);
	}

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEBUG_OUTPUT);

		glDebugMessageCallback(MessageCallback, 0);

		WI_CORE_ASSERT(status, "Failed to load glad");

		WI_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		WI_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		WI_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
