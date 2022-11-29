#include "wipch.h"
#include "PerspectiveCameraController.h"

#include "Wismut/Core/Core.h"
#include "Wismut/Core/Input.h"
#include "Wismut/Events/KeyEvent.h"

namespace Wi
{
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float near, float far)
		: m_Camera(aspectRatio, 45.0f, near, far), m_AspectRatio(aspectRatio)
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
		if (event.GetMouseButton() == Key::ButtonLeft)
		{
			m_IsRotating = true;
			m_InitialMousePosition = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
			return true;
		}
		return false;
	}

	bool PerspectiveCameraController::OnMouseReleased(MouseButtonReleasedEvent& event)
	{
		if (event.GetMouseButton() == Key::ButtonLeft)
		{
			m_IsRotating = false;
			return true;
		}

		return false;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& event)
	{
		if (m_IsRotating)
		{
			glm::vec2 mouse = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
			glm::vec2 delta = mouse - m_InitialMousePosition;
			m_InitialMousePosition = mouse;
			m_Camera.SetRotation(m_Camera.GetPitch() + delta.x * 0.002f, m_Camera.GetYaw() + delta.y * 0.002f);
			return true;
		}

		return false;
	}

	bool PerspectiveCameraController::OnMouseScroll(MouseScrolledEvent& event)
	{
		return false;
	}

	void PerspectiveCameraController::OnUpdate()
	{
		if (Input::IsKeyPressed(Key::W))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetForwardDirection() * m_TranslationSpeed);
		}

		if (Input::IsKeyPressed(Key::S))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetForwardDirection() * m_TranslationSpeed);
		}

		if (Input::IsKeyPressed(Key::A))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRightDirection() * m_TranslationSpeed);
		}

		if (Input::IsKeyPressed(Key::D))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRightDirection() * m_TranslationSpeed);
		}

		if (Input::IsKeyPressed(Key::Space))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, 1, 0) * m_TranslationSpeed);
		}

		if (Input::IsKeyPressed(Key::LeftShift))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() - glm::vec3(0, 1, 0) * m_TranslationSpeed);
		}
	}
}
