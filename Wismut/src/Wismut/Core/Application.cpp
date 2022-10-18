#include "wipch.h"
#include "Application.h"

#include "Assert.h"
#include "Core.h"

namespace Wi
{
	bool Application::s_IsInitialized;

	Application::Application()
	{
		WI_CORE_ASSERT(!s_IsInitialized, "Application has already initialized");

		m_Window = Window::Create();

		s_IsInitialized = true;
	}

	void Application::Run() const
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}
}
