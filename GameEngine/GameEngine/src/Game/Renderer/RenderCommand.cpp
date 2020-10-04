#include "gepch.h"
#include "Game/Renderer/RenderCommand.h"

namespace GameEngine {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}