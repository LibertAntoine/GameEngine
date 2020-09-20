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
	
}

void Sandbox2D::OnAttach()
{
	GE_PROFILE_FUNCTION();

	m_CheckerboardTexture = GameEngine::Texture2D::Create("assets/textures/logo.png");
	m_SpriteSheet = GameEngine::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2D::OnDetach()
{
	GE_PROFILE_FUNCTION()
}

void Sandbox2D::OnUpdate(GameEngine::Timestep ts)
{
	GE_PROFILE_FUNCTION()

	GameEngine::Renderer2D::ResetStats();
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
		GameEngine::Renderer2D::DrawRotatedQuad({ -2.0f,  2.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		GameEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		GameEngine::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		GameEngine::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.3f, 1.0f));
		GameEngine::Renderer2D::EndScene();

		GameEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 0.5f) / 10.0f, 0.4f, (y + 0.5f) / 10.0f, 1.0f };
				GameEngine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		GameEngine::Renderer2D::EndScene();

		if (GameEngine::Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_LEFT))
		{
			auto [x, y] = GameEngine::Input::GetMousePosition();
			auto width = GameEngine::Application::Get().GetWindow().GetWidth();
			auto height = GameEngine::Application::Get().GetWindow().GetHeight();

			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();
			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_Particle.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 50; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		GameEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		GameEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f, 0.1f }, { 10.0f, 10.0f }, m_SpriteSheet);
		GameEngine::Renderer2D::EndScene();


		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	}

}

void Sandbox2D::OnImGuiRender()
{
	GE_PROFILE_FUNCTION()

	ImGui::Begin("Settings");

	auto stats = GameEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVextexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(GameEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
