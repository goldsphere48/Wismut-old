#pragma once

namespace Wi
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;
		virtual void SetData(const void* data, uint32_t offset, size_t size) = 0;

		static Ref<UniformBuffer> Create(size_t size, uint8_t binding);
	};
}
