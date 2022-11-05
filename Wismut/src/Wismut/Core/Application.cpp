#include "wipch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

#include "Assert.h"
#include "Core.h"
#include <glad/glad.h>

#include "Wismut/Renderer/BufferLayout.h"
#include "Wismut/Renderer/IndexBuffer.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/VertexBuffer.h"

namespace Wi
{
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(Render::ShaderDataType type)
	{
		switch (type)
		{
			case Render::ShaderDataType::Float:    return GL_FLOAT;
			case Render::ShaderDataType::Float2:   return GL_FLOAT;
			case Render::ShaderDataType::Float3:   return GL_FLOAT;
			case Render::ShaderDataType::Float4:   return GL_FLOAT;
			case Render::ShaderDataType::Mat3:     return GL_FLOAT;
			case Render::ShaderDataType::Mat4:     return GL_FLOAT;
			case Render::ShaderDataType::Int:      return GL_INT;
			case Render::ShaderDataType::Int2:     return GL_INT;
			case Render::ShaderDataType::Int3:     return GL_INT;
			case Render::ShaderDataType::Int4:     return GL_INT;
			case Render::ShaderDataType::Bool:     return GL_BOOL;
		}

		WI_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

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
		uint32_t vertexArray;

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
		};

		std::shared_ptr<Render::VertexBuffer> vertexBuffer = Render::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->Bind();

		std::shared_ptr<Render::IndexBuffer> indexBuffer = Render::IndexBuffer::Create(indices, 3);
		indexBuffer->Bind();

		Render::BufferLayout layout {
			{ Render::ShaderDataType::Float3, "u_Position" },
			{ Render::ShaderDataType::Float3, "u_Color" },
		};

		vertexBuffer->SetLayout(layout);

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index++);
			glVertexAttribPointer(
				index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				vertexBuffer->GetLayout().GetStride(), 
				reinterpret_cast<const void*>(element.Offset)
			);
		}

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 3));

		std::shared_ptr<Render::Shader> shader = Render::Shader::Create("assets/test.glsl");
		shader->Bind();

		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);

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
