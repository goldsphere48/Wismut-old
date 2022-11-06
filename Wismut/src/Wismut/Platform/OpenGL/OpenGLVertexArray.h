#pragma once
#include "Wismut/Renderer/VertexArray.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			class VertexArray : public Render::VertexArray
			{
			public:
				VertexArray();
				~VertexArray() override;
				void Bind() const override;
				void Unbind() const override;
				void AddVertexBuffer(const std::shared_ptr<Render::VertexBuffer>& buffer) override;
				void SetIndexBuffer(const std::shared_ptr<Render::IndexBuffer>& buffer) override;

			private:
				std::vector<std::shared_ptr<Render::VertexBuffer>> m_VertexBuffers;
				std::shared_ptr<Render::IndexBuffer> m_IndexBuffer;
				uint32_t m_RendererID;
			};
		}
	}
}
