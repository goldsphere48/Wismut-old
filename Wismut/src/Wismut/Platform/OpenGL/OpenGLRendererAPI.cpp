#include "wipch.h"
#include "Wismut/Platform/OpenGL/OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace Wi
{
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message, const void* userParam)
	{
		if (severity == GL_DEBUG_SEVERITY_HIGH)
			WI_CORE_ERROR("OpenGL Error: Type: {0}, severity: {1}, message: {2}", type, severity, message);

		if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_LOW)
			WI_CORE_WARN("OpenGL Warning: Type: {0}, severity: {1}, message: {2}", type, severity, message);

		if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
			WI_CORE_WARN("OpenGL Warning: DEPRECATED BEHAVIOUR Type: {0}, severity: {1}, message: {2}", type, severity, message);
	}

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDebugMessageCallback(MessageCallback, 0);
	}

	void OpenGLRendererAPI::Clear(glm::vec4 color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) const
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetViewport(int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
