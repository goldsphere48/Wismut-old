#pragma once

#include "Wismut/Core/Timestep.h"
#include "Wismut/Events/Event.h"

namespace Wi
{
	class Layer
	{
	public:
		Layer(std::string name = "Layer")
			: m_DebugName(std::move(name)) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}
