#pragma once

#include "wipch.h"

#include <functional>

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
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
			
		}

		template<typename T>
		void Dispatch(const std::function<void(T)>& handler)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				handler(static_cast<T>(m_Event));
			}
		}

	private:
		Event& m_Event;
	};
}
