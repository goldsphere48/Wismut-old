#include "wipch.h"
#include "OrthographicCamera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/transform.hpp"

namespace Wi
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:	m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
			m_ViewMatrix(1.0f),
			m_Position(glm::vec3(0)),
			m_Rotation(0.0f)
	{
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

	void OrthographicCamera::SetPosition(glm::vec3 position)
	{
		m_Position = position;
		UpdateView();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		UpdateView();
	}

	const glm::mat4& OrthographicCamera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4& OrthographicCamera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	glm::mat4 OrthographicCamera::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::UpdateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
	}
}
