#pragma once
#include "Wismut/Renderer/PerspectiveCamera.h"
#include "Wismut/Core/Timestep.h"
#include "Wismut/Events/Event.h"
#include "Wismut/Events/MouseEvent.h"

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
		bool OnMousePressed(MouseButtonPressedEvent& event);
		bool OnMouseReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScroll(MouseScrolledEvent& event);

	private:
		PerspectiveCamera m_Camera;
		bool m_IsRotating = false;
		bool m_IsDragging = false;
		glm::vec2 m_InitialMousePosition;
		glm::vec3 m_CameraPosition = {0, 0, 0};
		float m_TranslationSpeed = 5.0f;
		float m_DragSpeed = 0.002f;
		float m_AspectRatio;
		float m_Fov = 45.0f;
	};
}