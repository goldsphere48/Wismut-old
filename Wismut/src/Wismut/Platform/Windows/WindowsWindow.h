#pragma once

#include <Wismut/Core/Window.h>
#include <GLFW/glfw3.h>

namespace Wi
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		void Initialize(const WindowProps& props);
		void Shutdown() const;

		int GetWidth() const override { return m_Data.Width; }
		int GetHeight() const override { return m_Data.Height; }
		bool IsVSync() const override { return m_Data.IsVSync; }
		void SetVSync(bool value) override;
		void* GetNativeWindow() const override { return m_Window; }
		void OnUpdate() override;

	private:
		struct WindowData
		{
			std::string Title;
			int Width;
			int Height;
			bool IsVSync;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;
	};
}
