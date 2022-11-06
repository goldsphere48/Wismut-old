#include "wipch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Wi
{
	void OpenGLRendererAPI::Clear(glm::vec4 color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
