#include "wipch.h"
#include "Wismut/Renderer/Renderer.h"

namespace Wi
{
	Renderer::SceneData Renderer::s_SceneData;
	ShaderLibrary Renderer::m_ShaderLibrary;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::BeginScene(const PerspectiveCamera& camera)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform)
	{
		shader->Bind();
		shader->SetMat4("u_Transform", transform);
		shader->SetMat4("u_ViewProjection", s_SceneData.ViewProjectionMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}
}
