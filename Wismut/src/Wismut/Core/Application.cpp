#include "wipch.h"
#include "Application.h"

#include "Assert.h"
#include "Core.h"

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

	void Application::Run() const
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(WI_BIND_EVENT_FN(Application::OnWindowClose));
	}

	void Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
	}
}
