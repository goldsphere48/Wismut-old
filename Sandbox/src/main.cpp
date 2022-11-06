#include <Wismut.h>

#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/VertexArray.h"

class MyLayer : public Wi::Layer
{
public:
	MyLayer()
		: Wi::Layer("Layer")
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
		};

		m_VertexArray = Wi::VertexArray::Create();

		auto vertexBuffer = Wi::VertexBuffer::Create(vertices, sizeof(vertices));
		auto indexBuffer = Wi::IndexBuffer::Create(indices, 3);

		auto layout = Wi::BufferLayout
		{
			{ Wi::ShaderDataType::Float3, "u_Position" },
			{ Wi::ShaderDataType::Float3, "u_Color" },
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader = Wi::Shader::Create("assets/test.glsl");
	}

	void OnUpdate() override
	{
		Wi::Renderer::BeginScene();
		m_Shader->Bind();
		Wi::Renderer::Submit(m_VertexArray);
		Wi::Renderer::EndScene();
	}

private:
	std::shared_ptr<Wi::VertexArray> m_VertexArray;
	std::shared_ptr<Wi::Shader> m_Shader;
};

class MyApplication : public Wi::Application
{
public:
	MyApplication()
	{
		PushLayer(new MyLayer);
	}
};

Wi::Application* Wi::CreateApplication()
{
	return new MyApplication();
}
