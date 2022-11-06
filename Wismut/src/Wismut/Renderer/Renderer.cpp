#include "wipch.h"
#include "Renderer.h"


namespace Wi
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}
}
