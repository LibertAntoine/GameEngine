#include "gepch.h"
#include "Game/Renderer/FrameBuffer.h"
#include "Game/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace GameEngine {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}