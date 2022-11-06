#include "wipch.h"
#include "RenderCommand.h"

#include "Wismut/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wi
{
	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
