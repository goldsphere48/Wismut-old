#include "wipch.h"
#include "Wismut/Renderer/Renderer.h"

namespace Wi
{
	Renderer::SceneData Renderer::s_SceneData;
	ShaderLibrary Renderer::s_ShaderLibrary;
	Scope<RendererAPI> Renderer::s_RendererAPI = nullptr;

	void Renderer::Init()
	{
		s_RendererAPI = RendererAPI::Create();
	}

	void Renderer::OnWindowResize(int width, int height)
	{
		s_RendererAPI->SetViewport(width, height);
	}

	void Renderer::BeginFrame(const glm::mat4& camera)
	{
		s_SceneData.ViewProjectionMatrix = camera;
	}

	void Renderer::EndFrame()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform)
	{
		shader->Bind();
		shader->SetMat4("u_Transform", transform);
		shader->SetMat4("u_ViewProjection", s_SceneData.ViewProjectionMatrix);
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	void Renderer::Clear(glm::vec4 clearColor)
	{
		s_RendererAPI->Clear(clearColor);
	}
}
