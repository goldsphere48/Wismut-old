#pragma once
#include "Wismut/Core/Input.h"

namespace Wi
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(KeyCode key) override;
		bool IsKeyReleasedImpl(KeyCode key) override;
		bool IsMouseButtonPressedImpl(MouseCode button) override;
		bool IsMouseButtonReleasedImpl(MouseCode button) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}
