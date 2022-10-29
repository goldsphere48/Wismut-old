#pragma once
#include "Event.h"

namespace Wi
{
	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return MouseButton; }

	protected:
		MouseButtonEvent(int mouseButton)
			: MouseButton(mouseButton)
		{

		}

	protected:
		int MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton)
		{
			
		}

		EVENT_TYPE(MouseButtonPressed)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePressedEvent: " << MouseButton;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton)
		{

		}

		EVENT_TYPE(MouseButtonReleased)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleasedEvent: " << MouseButton;
			return ss.str();
		}
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int mouseX, int mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY)
		{
			
		}

		EVENT_TYPE(MouseMoved)

		int GetMouseX() const { return m_MouseX; }
		int GetMouseY() const { return m_MouseY; }

	private:
		int m_MouseX;
		int m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int xOffset, int yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset)
		{
			
		}

		EVENT_TYPE(MouseScrolled)

		int GetOffsetX() const { return m_xOffset; }
		int GetOffsetY() const { return m_yOffset; }

	private:
		int m_xOffset;
		int m_yOffset;
	};
}
