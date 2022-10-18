#pragma once

#include "wipch.h"

namespace Wi
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "Wi App", int width = 1600, int height = 900)
			: Title(title), Width(width), Height(height)
		{
			
		}

		std::string Title;
		int Width;
		int Height;
	};

	class Window
	{
	public:
		virtual ~Window() = default;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool value) = 0;
		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	};
}
