#pragma once
#include "Wismut/Core/Events/Event.h"
#include "Wismut/Core/MouseCodes.h"

namespace Wi
{
	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return MouseButton; }

	protected:
		MouseButtonEvent(MouseCode mouseButton)
			: MouseButton(mouseButton)
		{

		}

	protected:
		MouseCode MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode mouseButton)
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
		MouseButtonReleasedEvent(MouseCode mouseButton)
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
		MouseMovedEvent(float mouseX, float mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY)
		{
			
		}

		EVENT_TYPE(MouseMoved)

		float GetMouseX() const { return m_MouseX; }
		float GetMouseY() const { return m_MouseY; }

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset)
		{
			
		}

		EVENT_TYPE(MouseScrolled)

		float GetOffsetX() const { return m_xOffset; }
		float GetOffsetY() const { return m_yOffset; }

	private:
		float m_xOffset;
		float m_yOffset;
	};
}
