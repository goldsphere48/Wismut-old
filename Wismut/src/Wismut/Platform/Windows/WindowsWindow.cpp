#include "wipch.h"
#include "WindowsWindow.h"
#include <Wismut/Core/Log.h>
#include <Wismut/Core/Core.h>
#include <Wismut/Core/Assert.h>

#include "Wismut/Events/KeyEvent.h"
#include "Wismut/Events/MouseEvent.h"
#include "Wismut/Events/WindowEvents.h"

#include <glad/glad.h>

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

		WI_CORE_ASSERT(m_Window, "Failed to create a window");

		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		WI_CORE_ASSERT(status, "Failed to load glad");

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
			MouseMovedEvent e(x, y);
			data->EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data->EventCallback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data->EventCallback(e);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent e(xOffset, yOffset);
			data->EventCallback(e);
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

	void WindowsWindow::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::SetEventCallback(std::function<void(Event&)> callback)
	{
		m_Data.EventCallback = callback;
	}
}
