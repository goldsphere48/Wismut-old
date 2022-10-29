#include "wipch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

#include "Assert.h"
#include "Core.h"
#include <glad/glad.h>

namespace Wi
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WI_CORE_ASSERT(!s_Instance, "Application has already initialized");

		m_Window = Window::Create();
		m_Window->SetEventCallback(WI_BIND_EVENT_FN(Application::OnEvent));

		s_Instance = this;
		m_Running = true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(32.f/255.f, 42.f/255.f, 6.f/255.f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
