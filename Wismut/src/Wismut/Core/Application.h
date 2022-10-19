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
		static Application* GetInstance() { return s_Instance; }

	private:
		void OnWindowClose(WindowCloseEvent& event);

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	Application* CreateApplication();
}
