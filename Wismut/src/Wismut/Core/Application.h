#pragma once
#include "Window.h"
#include "Wismut/Events/Event.h"
#include "Wismut/Events/WindowEvents.h"
#include "LayerStack.h"
#include "Wismut/ImGui/ImGuiLayer.h"

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
		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		LayerStack m_LayerStack;
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		float m_LastFrameTime = 0.0f;
	};

	Application* CreateApplication();
}
