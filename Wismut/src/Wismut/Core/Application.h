#pragma once
#include "Window.h"
#include "Wismut/Events/Event.h"
#include "Wismut/Events/WindowEvents.h"

namespace Wi
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run() const;
		void OnEvent(Event& event);

	private:
		void OnWindowClose(WindowCloseEvent& event);

	private:
		static bool s_IsInitialized;
		std::unique_ptr<Window> m_Window;
	};

	Application* CreateApplication();
}
