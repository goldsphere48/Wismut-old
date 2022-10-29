#pragma once
#include "Wismut/Core/Layer.h"

namespace Wi
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(const Event& event) override;

	private:
		float m_Time;
	};
}
