#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Wi
{
	namespace Render
	{
		class VertexArray
		{
		public:
			virtual ~VertexArray() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
			virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

			static std::shared_ptr<VertexArray> Create();
		};
	}
}
