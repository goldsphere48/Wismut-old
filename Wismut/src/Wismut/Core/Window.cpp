#include "wipch.h"
#include "Wismut/Core/Window.h"

#ifdef WI_PLATFORM_WIN
#include "Wismut/Platform/Windows/WindowsWindow.h"
#endif

namespace Wi
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef WI_PLATFORM_WIN
		return CreateScope<WindowsWindow>(props);
#endif
	}
}
