#include "wipch.h"
#include "Window.h"

#ifdef WI_PLATFORM_WIN
#include <Wismut/Platform/Windows/WindowsWindow.h>
#endif

namespace Wi
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
#ifdef WI_PLATFORM_WIN
		return std::make_unique<WindowsWindow>(props);
#endif
	}
}
