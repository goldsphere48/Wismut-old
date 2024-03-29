#pragma once
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

namespace Wi
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

	public:
		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(glm::vec3 position);
		void SetRotation(float rotation);

		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::vec3& GetPosition() const { return m_Position; }
		glm::quat GetOrientation() const; 
		glm::mat4 GetViewProjectionMatrix() const;
		float GetRotation() const { return m_Rotation; }

	private:
		void UpdateView();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}

