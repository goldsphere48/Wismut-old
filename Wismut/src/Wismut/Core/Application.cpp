#include "wipch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

#include "Assert.h"
#include "Core.h"
#include <glad/glad.h>

#include "Wismut/Renderer/BufferLayout.h"
#include "Wismut/Renderer/IndexBuffer.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/VertexArray.h"
#include "Wismut/Renderer/VertexBuffer.h"

namespace Wi
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WI_CORE_ASSERT(!s_Instance, "Application has already initialized");

		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(WI_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_Running = true;
	}

	void Application::Run()
	{
		std::shared_ptr<Render::VertexArray> vertexArray = Render::VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
		};

		std::shared_ptr<Render::VertexBuffer> vertexBuffer = Render::VertexBuffer::Create(vertices, sizeof(vertices));

		Render::BufferLayout layout {
			{ Render::ShaderDataType::Float3, "u_Position" },
			{ Render::ShaderDataType::Float3, "u_Color" },
		};

		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Render::IndexBuffer> indexBuffer = Render::IndexBuffer::Create(indices, 3);
		vertexArray->SetIndexBuffer(indexBuffer);

		std::shared_ptr<Render::Shader> shader = Render::Shader::Create("assets/test.glsl");

		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(WI_BIND_EVENT_FN(Application::OnWindowClose));

		WI_CORE_TRACE("{0}", event);

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.Handled)
				break;

			(*it)->OnEvent(event);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}
