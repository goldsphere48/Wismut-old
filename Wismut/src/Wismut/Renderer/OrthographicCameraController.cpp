#include "wipch.h"
#include "OrthographicCameraController.h"

#include "Wismut/Core/Core.h"
#include "Wismut/Core/Input.h"
#include <cmath>

#include "Wismut/Core/Log.h"

namespace Wi
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: m_ZoomLevel(1),
		  m_AspectRatio(aspectRatio),
		  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate()
	{
		if (Input::IsKeyPressed(Key::Q))
		{
			m_Rotation -= m_RotationSpeed;
		}

		if (Input::IsKeyPressed(Key::E))
		{
			m_Rotation += m_RotationSpeed;
		}

		if (m_Rotation > 180.0f)
			m_Rotation -= 360.0f;
		else if (m_Rotation <= -180.0f)
			m_Rotation += 360.0f;

		m_Camera.SetRotation(m_Rotation);
		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(WI_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(WI_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(WI_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(WI_BIND_EVENT_FN(OrthographicCameraController::OnMouseMoved));
	}

	bool OrthographicCameraController::OnMouseButtonPressed(MouseButtonPressedEvent& event)
	{
		if (event.GetMouseButton() == Key::ButtonMiddle)
		{
			if (!m_IsDragging)
				m_InitialMousePosition = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
			m_IsDragging = true;
			return true;
		}
		return false;
	}

	bool OrthographicCameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& event)
	{
		if (event.GetMouseButton() == Key::ButtonMiddle)
		{
			m_IsDragging = false;
			return true;
		}
		return false;
	}

	bool OrthographicCameraController::OnMouseMoved(MouseMovedEvent& event)
	{
		if (m_IsDragging) {
			glm::vec2 mouse = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
			glm::vec2 delta = mouse - m_InitialMousePosition;
			m_InitialMousePosition = mouse;
			m_CameraPosition.x -= delta.x * m_TranslationSpeed;
			m_CameraPosition.y += delta.y * m_TranslationSpeed;
			return true;
		}

		return false;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetOffsetY() * 0.25f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 10.0f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
