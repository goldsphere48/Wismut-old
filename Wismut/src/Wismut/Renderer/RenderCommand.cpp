#include "wipch.h"
#include "Wismut/Renderer/RenderCommand.h"
#include "Wismut/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wi
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
