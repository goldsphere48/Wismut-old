#include "wipch.h"
#include "Wismut/Platform/Windows/WindowsWindow.h"
#include <glad/glad.h>
#include "Wismut/Core/Events/KeyEvent.h"
#include "Wismut/Core/Events/MouseEvent.h"
#include "Wismut/Core/Events/WindowEvents.h"
#include "Wismut/Platform/OpenGL/OpenGLContext.h"

namespace Wi
{
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		WI_CORE_INFO("Creating window");
		Initialize(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		WI_CORE_INFO("Window shutdown");
		Shutdown();
	}

	void WindowsWindow::Initialize(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		SetVSync(true);

		WI_CORE_ASSERT(glfwInit(), "Failed to init glfw");

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		glfwWindowHint(GLFW_SAMPLES, 16);
		WI_CORE_ASSERT(m_Window, "Failed to create a window");

		m_Context = CreateScope<OpenGLContext>(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent e;
			data->EventCallback(e);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowResizeEvent e(width, height);
			data->Width = width;
			data->Height = height;
			data->EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, false);
					data->EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data->EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, true);
					data->EventCallback(e);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent e(static_cast<float>(x), static_cast<float>(y));
			data->EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(static_cast<uint16_t>(button));
					data->EventCallback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(static_cast<uint16_t>(button));
					data->EventCallback(e);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent e((float)xOffset, (float)yOffset);
			data->EventCallback(e);
		});

		glfwSetErrorCallback([](int x, const char* msg)
		{
			WI_CORE_ERROR(msg);
		});
	}

	void WindowsWindow::Shutdown() const
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetVSync(bool value)
	{
		m_Data.IsVSync = value;
		glfwSwapInterval(value);
	}

	void WindowsWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void WindowsWindow::SetEventCallback(std::function<void(Event&)> callback)
	{
		m_Data.EventCallback = callback;
	}

	void WindowsWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
