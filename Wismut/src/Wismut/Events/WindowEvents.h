#pragma once
#include "Wismut/Events/Event.h"

namespace Wi
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_TYPE(WindowClose);
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height)
		{
			
		}

		EVENT_TYPE(WindowResize);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resize: " << m_Width << " " << m_Height;
			return ss.str();
		}

	private:
		int m_Width;
		int m_Height;
	};
}
