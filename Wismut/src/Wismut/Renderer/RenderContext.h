#pragma once

namespace Wi
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}