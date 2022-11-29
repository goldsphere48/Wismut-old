#pragma once
#include "Camera.h"

namespace Wi
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float top, float right, float bottom);

	public:
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(glm::vec3 position);
		void SetRotation(float rotation);

		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		glm::mat4 GetViewProjectionMatrix() const;

	private:
		void UpdateView();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}

