#pragma once
#include "Wismut/Core/KeyCodes.h"
#include "Wismut/Core/MouseCodes.h"

namespace Wi
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		static bool IsKeyReleased(KeyCode key) { return s_Instance->IsKeyReleasedImpl(key); }

		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static bool IsMouseButtonReleased(MouseCode button) { return s_Instance->IsMouseButtonReleasedImpl(button); }

		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsKeyReleasedImpl(KeyCode key) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual bool IsMouseButtonReleasedImpl(MouseCode button) = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual  std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Scope<Input> s_Instance;
	};
}
