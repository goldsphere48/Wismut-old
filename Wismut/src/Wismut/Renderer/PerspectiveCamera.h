#pragma once
#include "glm/glm.hpp"
#include "glm/detail/type_quat.hpp"

namespace Wi
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float aspectRatio, float fov, float near, float far);

		const glm::mat4& GetView() const;
		const glm::mat4& GetProjection() const;

		glm::mat4 GetViewProjectionMatrix() const;
		glm::quat GetOrientation() const;
		glm::vec3 GetPosition() const { return m_Position; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetForwardDirection() const;
		glm::vec3 GetRightDirection() const;
		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }

		void SetProjection(float aspectRatio, float fov, float near, float far);
		void SetPosition(glm::vec3 position);
		void SetRotation(float pitch, float yaw);

	private:
		void UpdateView();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Position = {0, 0, 0};
		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
	};
}
