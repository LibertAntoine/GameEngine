#include "Sandbox2D.h"
#include "imgui/Imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
	
}

Sandbox2D::~Sandbox2D()
{
	;
}

void Sandbox2D::OnAttach()
{
	GE_PROFILE_FUNCTION();

	m_CheckerboardTexture = GameEngine::Texture2D::Create("assets/textures/logo.png");
}

void Sandbox2D::OnDetach()
{
	GE_PROFILE_FUNCTION()
}

void Sandbox2D::OnUpdate(GameEngine::Timestep ts)
{
	GE_PROFILE_FUNCTION()

	{
		GE_PROFILE_SCOPE("m_CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		GE_PROFILE_SCOPE("Renderer Prep");
		GameEngine::RenderCommand::SetClearColor({ 1, 0.5, 0.5, 1 });
		GameEngine::RenderCommand::Clear();
	}

	{
		GE_PROFILE_SCOPE("Renderer Draw");
		GameEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		GameEngine::Renderer2D::DrawRotatedQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		GameEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		GameEngine::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.3f, 1.0f));
		GameEngine::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender() 
{
	GE_PROFILE_FUNCTION()

	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(GameEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
