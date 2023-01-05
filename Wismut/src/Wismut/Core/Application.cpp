#include "wipch.h"
#include "Wismut/Core/Application.h"
#include "Wismut/Core/Timestep.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Utils/Time.h"

namespace Wi
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WI_CORE_ASSERT(!s_Instance, "Application has already initialized");

		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(WI_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_Running = true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			const float time = Time::GetTime();
			const Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			Renderer::Clear({ 0.8, 0.6, 0.6, 1.0 });

			if (!m_Minimized)
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(ts);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return OnWindowClose(e); });
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) { return OnWindowResize(e); });

		WI_CORE_TRACE("{0}", event);

		for (const auto& it : std::ranges::reverse_view(m_LayerStack))
		{
			if (event.Handled)
				break;

			it->OnEvent(event);
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

	bool Application::OnWindowClose(const WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(const WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0) 
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}
