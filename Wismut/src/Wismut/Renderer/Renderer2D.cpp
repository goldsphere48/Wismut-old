#include "wipch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "glad/glad.h"

namespace Wi
{
	Renderer2D::SceneData Renderer2D::s_SceneData;
	Renderer2D::Renderer2DData Renderer2D::s_Data;

	void Renderer2D::Init()
	{
		s_SceneData.ShaderLibrary = CreateRef<ShaderLibrary>();
		s_SceneData.ShaderLibrary->Load("assets/FlatColorShader.glsl");

		s_Data.FlatColorShader = s_SceneData.ShaderLibrary->Get("FlatColorShader");

		const unsigned int whiteTextureData = 0xFFFFFF;
		s_Data.WhiteTexture = Texture2D::Create(1, 1, &whiteTextureData);

		float quadVertices[] = 
		{
			-1.0f, -1.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 1.0f, 0.0f
		};
		s_Data.QuadVertexBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices));

		unsigned int indices[] = 
		{
			0, 1, 2,
			0, 3, 2
		};

		s_Data.QuadIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		s_Data.VertexArray = VertexArray::Create();
		BufferLayout layout = {
			BufferLayoutElement(ShaderDataType::Float2, "VertexPosition"),
			BufferLayoutElement(ShaderDataType::Float2, "VertexTexCoord"),
		};

		s_Data.QuadVertexBuffer->SetLayout(layout);
		s_Data.VertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
		s_Data.VertexArray->SetIndexBuffer(s_Data.QuadIndexBuffer);
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::mat4 transform)
	{
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->SetMat4("u_MVP", s_SceneData.ViewProjectionMatrix * transform);
		s_Data.FlatColorShader->SetFloat4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		RenderCommand::DrawIndexed(s_Data.VertexArray);
	}
}
