#pragma once

#include <memory>
#include "Game/Renderer/Buffer.h"

namespace GameEngine {

	class VertexArray
	{
	public: 
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual Ref<IndexBuffer> GetIndexBuffers() const = 0;


		static VertexArray* Create();
	};
}