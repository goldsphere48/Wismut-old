#pragma once
#include "Wismut/Core/Events/Event.h"

namespace Wi
{
	class ApplicationTickEvent : public Event
	{
	public:
		ApplicationTickEvent() = default;
		EVENT_TYPE(AppTick);
	};

	class ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent() = default;
		EVENT_TYPE(AppUpdate);
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() = default;
		EVENT_TYPE(AppRender);
	};
}
