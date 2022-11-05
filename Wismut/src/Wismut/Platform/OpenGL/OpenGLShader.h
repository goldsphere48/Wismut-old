#pragma once
#include "glad/glad.h"
#include "Wismut/Renderer/Shader.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			class Shader : public Render::Shader
			{
			public:
				Shader(const std::string& vertexSource, const std::string& fragmentSource);
				Shader(const std::string& filepath);

				~Shader() override;

				void Bind() override;
				void Unbind() override;

			private:
				std::unordered_map<GLenum, std::string> SplitShader(const std::string& source);
				void CreateProgram(std::unordered_map<GLenum, std::string>&& sources);

			private:
				unsigned int m_RenderID;
			};
		}
	}
}
