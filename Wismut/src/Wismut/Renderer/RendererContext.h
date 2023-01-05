#pragma once

namespace Wi
{
	class RendererContext
	{
	public:
		virtual ~RendererContext() = default;
		virtual void Init() = 0;
	};
}