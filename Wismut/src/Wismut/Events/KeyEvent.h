#pragma once
#include "Event.h"

namespace Wi
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(int keyCode)
			: KeyCode(keyCode)
		{
			
		}

	protected:
		int KeyCode;
	};

	class KeyPressedEvent : KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, bool repeated)
			: KeyEvent(keyCode), m_IsRepeated(repeated)
		{
		}

		EVENT_TYPE(KeyPressed)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed: " << KeyCode << " " << m_IsRepeated;
			return ss.str();
		}

		bool IsRepeated() const { return m_IsRepeated; }

	private:
		bool m_IsRepeated;
	};

	class KeyReleasedEvent : KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{
		}

		EVENT_TYPE(KeyReleased)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << KeyCode;
			return ss.str();
		}
	};
}
