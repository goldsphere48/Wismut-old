#include "wipch.h"
#include "Wismut/Renderer/Camera/OrthographicCameraController.h"
#include "Wismut/Core/Input.h"

namespace Wi
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: m_ZoomLevel(1),
		  m_AspectRatio(aspectRatio),
		  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::Q))
		{
			m_Rotation -= m_RotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::E))
		{
			m_Rotation += m_RotationSpeed * ts;
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
		dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e) { return OnMouseButtonPressed(e); });
		dispatcher.Dispatch<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e) { return OnMouseButtonReleased(e); });
		dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& e) { return OnMouseScrolled(e); });
		dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e) { return OnMouseMoved(e); });
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) { return OnWindowResize(e); });
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
			m_CameraPosition -= m_Camera.GetOrientation() * glm::vec3(delta.x, -delta.y, 0.0f) * m_DragSpeed * m_ZoomLevel;
			return true;
		}

		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		m_AspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

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
