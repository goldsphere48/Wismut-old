#pragma once
#include "Wismut/Renderer/Camera/PerspectiveCamera.h"
#include "Wismut/Core/Timestep.h"
#include "Wismut/Core/Events/Event.h"
#include "Wismut/Core/Events/MouseEvent.h"

namespace Wi
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float near, float far);
		void OnEvent(Event& event);
		const PerspectiveCamera& GetCamera() const;
		void OnUpdate(Timestep ts);

	private:
		bool OnMousePressed(const MouseButtonPressedEvent& event);
		bool OnMouseReleased(const MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScroll(MouseScrolledEvent& event);

	private:
		PerspectiveCamera m_Camera;
		bool m_IsRotating = false;
		bool m_IsDragging = false;
		glm::vec2 m_InitialMousePosition = glm::vec2(0, 0);
		glm::vec3 m_CameraPosition = {0, 0, 0};
		float m_TranslationSpeed = 5.0f;
		float m_DragSpeed = 0.002f;
		float m_Fov = 45.0f;
	};
}
