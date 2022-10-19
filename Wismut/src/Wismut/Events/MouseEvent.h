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

	class MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int mouseButton)
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

	class MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int mouseButton)
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

	class MouseMoved : public Event
	{
	public:
		MouseMoved(int mouseX, int mouseY)
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

	class MouseScrolled : public Event
	{
	public:
		MouseScrolled(int xOffset, int yOffset)
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
