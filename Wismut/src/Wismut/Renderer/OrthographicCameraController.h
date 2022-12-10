#pragma once
#include "Wismut/Renderer/OrthographicCamera.h"
#include "Wismut/Core/Timestep.h"
#include "Wismut/Events/MouseEvent.h"

namespace Wi
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);

	private:
		float m_ZoomLevel;
		float m_AspectRatio;
		OrthographicCamera m_Camera;
		glm::vec2 m_InitialMousePosition = { 0, 0 };
		glm::vec3 m_CameraPosition = { 0, 0, 0 };
		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.01f;
		float m_TranslationSpeed = 5.0f;
		float m_DragSpeed = 0.002f;
		bool m_IsDragging = false;
	};
}
