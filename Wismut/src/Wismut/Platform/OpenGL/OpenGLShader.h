#pragma once
#include "glad/glad.h"
#include "Wismut/Renderer/Shader.h"

namespace Wi
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& filepath);

		~OpenGLShader() override;

		void Bind() override;
		void Unbind() override;

	private:
		std::unordered_map<GLenum, std::string> SplitShader(const std::string& source);
		void CreateProgram(std::unordered_map<GLenum, std::string>&& sources);

	private:
		uint32_t m_RenderID;
	};
}
