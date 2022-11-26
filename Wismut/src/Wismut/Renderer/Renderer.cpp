#include "wipch.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "RenderCommand.h"


namespace Wi
{
	Renderer::SceneData Renderer::s_SceneData;

	void Renderer::BeginScene(Camera camera)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4 transform)
	{
		shader->Bind();
		shader->SetMat4("u_Transform", transform);
		shader->SetMat4("u_ViewProjection", s_SceneData.ViewProjectionMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}
}
