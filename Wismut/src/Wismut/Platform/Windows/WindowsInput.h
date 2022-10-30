#pragma once
#include "Wismut/Core/Input.h"

namespace Wi
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int key) override;
		bool IsKeyReleasedImpl(int key) override;
		bool IsMouseButtonPressedImpl(int button) override;
		bool IsMouseButtonReleasedImpl(int button) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}
