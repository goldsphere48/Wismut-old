#pragma once
#include "Camera.h"

namespace Wi
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float top, float right, float bottom);

	public:
		const glm::mat4& GetViewProjectionMatrix() const;

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
	};
}

