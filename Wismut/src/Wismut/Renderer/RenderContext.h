#pragma once

namespace Wi
{
	namespace Render
	{
		class Context
		{
		public:
			virtual ~Context() = default;
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
		};
	}
}