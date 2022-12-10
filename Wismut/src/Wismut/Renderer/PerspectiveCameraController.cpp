#include "wipch.h"
#include "Wismut/Renderer/PerspectiveCameraController.h"
#include "Wismut/Core/Input.h"
#include "Wismut/Events/KeyEvent.h"

namespace Wi
{
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float zNear, float zFar)
		: m_Camera(aspectRatio, glm::radians(45.0f), zNear, zFar), m_AspectRatio(aspectRatio)
	{
	}

	void PerspectiveCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(WI_BIND_EVENT_FN(PerspectiveCameraController::OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(WI_BIND_EVENT_FN(PerspectiveCameraController::OnMouseReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(WI_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScroll));
		dispatcher.Dispatch<MouseMovedEvent>(WI_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	}

	const PerspectiveCamera& PerspectiveCameraController::GetCamera() const
	{
		return m_Camera;
	}

	bool PerspectiveCameraController::OnMousePressed(MouseButtonPressedEvent& event)
	{
		if (event.GetMouseButton() == Key::ButtonRight)
		{
			m_IsRotating = true;
			m_IsDragging = false;
			m_InitialMousePosition = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
			return true;
		}

		if (event.GetMouseButton() == Key::ButtonMiddle)
		{
			m_IsDragging = true;
			m_IsRotating = false;
			m_InitialMousePosition = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
			return true;
		}

		return false;
	}

	bool PerspectiveCameraController::OnMouseReleased(MouseButtonReleasedEvent& event)
	{
		if (event.GetMouseButton() == Key::ButtonRight)
		{
			m_IsRotating = false;
			return true;
		}

		if (event.GetMouseButton() == Key::ButtonMiddle)
		{
			m_IsDragging = false;
			return true;
		}

		return false;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& event)
	{
		glm::vec2 mouse = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
		glm::vec2 delta = mouse - m_InitialMousePosition;
		m_InitialMousePosition = mouse;

		if (m_IsRotating)
		{
			m_Camera.SetRotation(m_Camera.GetPitch() + delta.y * m_DragSpeed, m_Camera.GetYaw() + delta.x * m_DragSpeed);
			return true;
		}

		if (m_IsDragging)
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetOrientation() * glm::vec3(delta.x, -delta.y, 0.0f) * m_DragSpeed);
			return true;
		}

		return false;
	}

	bool PerspectiveCameraController::OnMouseScroll(MouseScrolledEvent& event)
	{
		m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetForwardDirection() * event.GetOffsetY() * 0.25f);
		return true;
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::W))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetForwardDirection() * (m_TranslationSpeed * ts));
		}

		if (Input::IsKeyPressed(Key::S))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetForwardDirection() * (m_TranslationSpeed * ts));
		}

		if (Input::IsKeyPressed(Key::A))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRightDirection() * (m_TranslationSpeed * ts));
		}

		if (Input::IsKeyPressed(Key::D))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRightDirection() * (m_TranslationSpeed * ts));
		}

		if (Input::IsKeyPressed(Key::Space))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, 1, 0) * (m_TranslationSpeed * ts));
		}

		if (Input::IsKeyPressed(Key::LeftShift))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - glm::vec3(0, 1, 0) * (m_TranslationSpeed * ts));
		}
	}
}
