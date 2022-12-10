#pragma once
#include "wipch.h"

namespace Wi
{
#define EVENT_TYPE(type) const char* GetName() const override { return #type; };\
						 static EventType GetStaticType() { return EventType::type; }\
						 EventType GetType() const override { return GetStaticType(); };

	enum EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	class Event
	{
	public:
		virtual const char* GetName() const = 0;
		virtual EventType GetType() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool Handled = false;
	};

	inline std::ostream& operator << (std::ostream& stream, const Event& event)
	{
		stream << event.ToString();
		return stream;
	}

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
			
		}

		template<typename T>
		void Dispatch(const std::function<bool(T)>& handler)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.Handled |= handler(static_cast<T&>(m_Event));
			}
		}

	private:
		Event& m_Event;
	};
}
