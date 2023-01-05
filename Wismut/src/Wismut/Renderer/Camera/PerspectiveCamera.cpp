#include "wipch.h"
#include "Wismut/Renderer/Camera/PerspectiveCamera.h"
#include <glm/gtx/quaternion.hpp>

namespace Wi
{
	PerspectiveCamera::PerspectiveCamera(float aspectRatio, float fov, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
		UpdateView();
	}

	const glm::mat4& PerspectiveCamera::GetView() const
	{
		return m_ViewMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetProjection() const
	{
		return m_ProjectionMatrix;
	}

	glm::mat4 PerspectiveCamera::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::quat PerspectiveCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	glm::vec3 PerspectiveCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0, 1, 0));
	}

	glm::vec3 PerspectiveCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0, 0, 1));
	}

	glm::vec3 PerspectiveCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1, 0, 0));
	}

	void PerspectiveCamera::SetProjection(float aspectRatio, float fov, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
	}

	void PerspectiveCamera::SetPosition(glm::vec3 position)
	{
		m_Position = position;
		UpdateView();
	}

	void PerspectiveCamera::SetRotation(float pitch, float yaw)
	{
		m_Pitch = pitch;
		m_Yaw = yaw;
		UpdateView();
	}

	void PerspectiveCamera::UpdateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(GetOrientation());
		m_ViewMatrix = glm::inverse(transform);
	}
}
