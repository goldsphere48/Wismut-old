#pragma once

namespace Wi
{
	namespace Render
	{
		class Shader
		{
		public:
			virtual ~Shader() = default;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			static std::shared_ptr<Shader> Create(const std::string& filepath);
			static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSource);

		protected:
			std::string ReadFile(const std::string& filepath);
		};
	}
}
