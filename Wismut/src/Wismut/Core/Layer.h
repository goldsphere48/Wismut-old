#pragma once

#include "wipch.h"

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
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnEvent(const Event& event) {}

		const std::string& GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}
