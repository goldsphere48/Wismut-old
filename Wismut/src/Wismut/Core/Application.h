#pragma once
#include "Window.h"
#include "Wismut/Events/Event.h"
#include "Wismut/Events/WindowEvents.h"
#include "LayerStack.h"

namespace Wi
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		static Application* GetInstance() { return s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		LayerStack m_LayerStack;
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	Application* CreateApplication();
}
