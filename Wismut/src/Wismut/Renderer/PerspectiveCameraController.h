#pragma once
#include "PerspectiveCamera.h"
#include "Wismut/Events/Event.h"
#include "Wismut/Events/KeyEvent.h"
#include "Wismut/Events/MouseEvent.h"

namespace Wi
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float near, float far);
		void OnEvent(Event& event);
		const PerspectiveCamera& GetCamera() const;
		void OnUpdate();

	private:
		bool OnMousePressed(MouseButtonPressedEvent& event);
		bool OnMouseReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScroll(MouseScrolledEvent& event);

	private:
		PerspectiveCamera m_Camera;
		bool m_IsRotating = false;
		glm::vec2 m_InitialMousePosition;
		glm::vec3 m_CameraPosition = {0, 0, 0};
		float m_TranslationSpeed = 0.005f;
		float m_AspectRatio;
		float m_Fov = 45.0f;
	};
}
