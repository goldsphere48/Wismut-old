#pragma once
#include "Wismut/Core/Window.h"
#include "Wismut/Core/Events/Event.h"
#include "Wismut/Core/Events/WindowEvents.h"
#include "Wismut/Core/LayerStack.h"
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
		bool OnWindowClose(const WindowCloseEvent& event);
		bool OnWindowResize(const WindowResizeEvent& event);

	private:
		LayerStack m_LayerStack;
		static Application* s_Instance;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;
	};

	Application* CreateApplication();
}
