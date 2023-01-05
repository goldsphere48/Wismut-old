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
		virtual ~Event() = default;
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

	template<typename T>
	concept EventClassType = requires
	{
		{ std::is_base_of<Event, T>() };
	};

	class EventDispatcher
	{
		template<EventClassType T>
		using EventHandleFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
			
		}

		template<EventClassType T>
		void Dispatch(const EventHandleFn<T>& handler)
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
