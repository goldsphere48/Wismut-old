#pragma once

#include <glm/glm.hpp>

namespace Wi
{
	class Camera
	{
	public:
		Camera(glm::mat4 viewProjectionMatrix)
			: m_ViewProjectionMatrix(viewProjectionMatrix)
		{
			
		}

		glm::mat4 GetViewProjectionMatrix() const
		{
			return m_ViewProjectionMatrix;
		}

	private:
		glm::mat4 m_ViewProjectionMatrix;
	};
}
