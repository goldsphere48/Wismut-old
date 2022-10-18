#pragma once
#include "Window.h"

namespace Wi
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run() const;

	public:
		static bool s_IsInitialized;
		std::unique_ptr<Window> m_Window;
	};

	Application* CreateApplication();
}
