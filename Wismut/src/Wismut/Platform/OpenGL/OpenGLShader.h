#pragma once
#include <glad/glad.h>
#include "Wismut/Renderer/Shader.h"

namespace Wi
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& filepath);

		~OpenGLShader() override;

		void Bind() override;
		void Unbind() override;

		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name, int* value, uint32_t count) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;

		const std::string& GetName() const override { return m_Name; }

	private:
		uint32_t GetLocation(const std::string name);
		std::unordered_map<GLenum, std::string> SplitShader(const std::string& source);
		void CreateProgram(std::unordered_map<GLenum, std::string>&& sources);

	private:
		std::unordered_map<std::string, uint32_t> m_CachedLocations;
		uint32_t m_RenderID;
		std::string m_Name;
	};
}
