#pragma once

namespace Wi
{
	namespace Render
	{
		enum class RenderAPI
		{
			None = 0,
			OpenGL = 1
		};

		class Renderer
		{
		public:
			static RenderAPI GetAPI() { return s_RenderAPI; }

		private:
			static RenderAPI s_RenderAPI;
		};
	}
}
