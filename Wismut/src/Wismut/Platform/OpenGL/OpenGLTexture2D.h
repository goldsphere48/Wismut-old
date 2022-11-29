#pragma once
#include "Wismut/Renderer/Texture.h"

namespace Wi
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D() override;

		uint32_t GetWidth() override;
		uint32_t GetHeight() override;
		void Bind() override;

	private:
		uint32_t m_RendererID;
		uint32_t m_Width;
		uint32_t m_Height;
	};
}
