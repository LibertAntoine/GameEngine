#include "gepch.h"
#include "Game/Renderer/VertexArray.h"

#include "Game/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GameEngine {

	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}