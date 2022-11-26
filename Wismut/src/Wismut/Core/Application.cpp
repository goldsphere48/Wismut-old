#include "wipch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

#include "Assert.h"
#include "Core.h"
#include "Wismut/Renderer/RenderCommand.h"

#include "Wismut/Renderer/Renderer.h"

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
		while (m_Running)
		{
			RenderCommand::Clear(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

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
