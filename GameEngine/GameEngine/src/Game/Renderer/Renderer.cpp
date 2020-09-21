#include "gepch.h"
#include "Game/Renderer/Renderer.h"
#include "Game/Renderer/Renderer2D.h"

namespace GameEngine {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;


	void Renderer::Init()
	{
		GE_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::ShutDown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		//mi->Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}