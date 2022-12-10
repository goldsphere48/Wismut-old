#pragma once

namespace Wi
{
	enum class ShaderDataType : uint8_t
	{
		None = 0,
		Bool,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:   return 1;
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		}

		WI_CORE_ASSERT(false, "Unknow ShaderDataType");
		return 0;
	}

	struct BufferLayoutElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferLayoutElement(ShaderDataType type, std::string&& name, bool normalized = false)
			: Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Bool:   return 1;
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			}

			WI_CORE_ASSERT(false, "Unknow ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{

	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferLayoutElement>& list)
			: m_Elements(list), m_Stride(0)
		{
			CalculateStrideAndOffsets();
		}

		const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }
		uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferLayoutElement>::const_iterator begin() const { return m_Elements.cbegin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return m_Elements.cend(); }

	private:
		void CalculateStrideAndOffsets()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				m_Stride += element.Size;
				offset += element.Size;
			}
		}

	private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride;
	};
}
