#pragma once
#include "Wismut/Core/Layer.h"

namespace Wi
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time;
	};
}
