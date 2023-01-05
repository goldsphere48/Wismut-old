#pragma once
#include "wipch.h"
#include "Wismut/Core/Events/Event.h"
#include "Wismut/Renderer/RendererContext.h"

namespace Wi
{
	struct WindowProps
	{
		WindowProps(std::string_view title = "Wi App", int width = 1600, int height = 900)
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
		virtual void PollEvents() = 0;
		virtual void SetEventCallback(std::function<void(Event&)> callback) = 0;
		virtual void SwapBuffers() = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());

	protected:
		Scope<RendererContext> m_Context;
	};
}
