#include "wipch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			static GLenum ShaderDataTypeToOpenGLBaseType(Render::ShaderDataType type)
			{
				switch (type)
				{
				case Render::ShaderDataType::Float:    return GL_FLOAT;
				case Render::ShaderDataType::Float2:   return GL_FLOAT;
				case Render::ShaderDataType::Float3:   return GL_FLOAT;
				case Render::ShaderDataType::Float4:   return GL_FLOAT;
				case Render::ShaderDataType::Mat3:     return GL_FLOAT;
				case Render::ShaderDataType::Mat4:     return GL_FLOAT;
				case Render::ShaderDataType::Int:      return GL_INT;
				case Render::ShaderDataType::Int2:     return GL_INT;
				case Render::ShaderDataType::Int3:     return GL_INT;
				case Render::ShaderDataType::Int4:     return GL_INT;
				case Render::ShaderDataType::Bool:     return GL_BOOL;
				}

				WI_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			}

			VertexArray::VertexArray()
			{
				glCreateVertexArrays(1, &m_RendererID);
			}

			VertexArray::~VertexArray()
			{
				glDeleteVertexArrays(1, &m_RendererID);
			}

			void VertexArray::Bind() const
			{
				glBindVertexArray(m_RendererID);
			}

			void VertexArray::Unbind() const
			{
				glBindVertexArray(0);
			}

			void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
			{
				WI_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

				glBindVertexArray(m_RendererID);
				buffer->Bind();

				uint32_t index = 0;
				for (const auto& element : buffer->GetLayout())
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(
						index,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						buffer->GetLayout().GetStride(),
						reinterpret_cast<const void*>(element.Offset)
					);
					index++;
				}

				m_VertexBuffers.push_back(buffer);
			}

			void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
			{
				glBindVertexArray(m_RendererID);
				buffer->Bind();

				m_IndexBuffer = buffer;
			}
		}
	}
}
