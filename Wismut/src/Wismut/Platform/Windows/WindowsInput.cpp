#include "wipch.h"
#include "Wismut/Platform/Windows/WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Wismut/Core/Application.h"

Wi::Scope<Wi::Input> Wi::Input::s_Instance = CreateScope<WindowsInput>();

bool Wi::WindowsInput::IsKeyPressedImpl(int key)
{
	const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	const auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Wi::WindowsInput::IsKeyReleasedImpl(int key)
{
	const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	const auto state = glfwGetKey(window, key);
	return state == GLFW_RELEASE;
}

bool Wi::WindowsInput::IsMouseButtonPressedImpl(int button)
{
	const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	const auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

bool Wi::WindowsInput::IsMouseButtonReleasedImpl(int button)
{
	const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	const auto state = glfwGetMouseButton(window, button);
	return state == GLFW_RELEASE;
}

float Wi::WindowsInput::GetMouseXImpl()
{
	auto [x, y] = GetMousePositionImpl();
	return x;
}

float Wi::WindowsInput::GetMouseYImpl()
{
	auto [x, y] = GetMousePositionImpl();
	return y;
}

std::pair<float, float> Wi::WindowsInput::GetMousePositionImpl()
{
	const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return { static_cast<float>(x), static_cast<float>(y) };
}
