#include "Sandbox2D.h"
#include <imgui/Imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 29;
static const char* s_MapTiles = 

"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWDDDDDDDDWWWWWWWWWWWWWWW"
"WWWWWDDDDDDDDDDWWWWWWWWWWWWWW"
"WWWWDDDDDDDDDDDDWWWWWWWWWWWWW"
"WWWDDDDWWWDDDDDDDDWWWWWWWWWWW"
"WWDDDDDWWWDDDDDDDDWWWWWWWWWWW"
"WWWDDDDDDDDDDDDDWWWWWWWWWWWWW"
"WWWWDDDDDDDDDDDWWWWWWWWWWWWWW"
"WWWWWDDDDDDDDDWWWWWWWWWWWWWWW"
"WWWWWWWDDDDDWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW";

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

	//m_TextureWater = GameEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
	s_TextureMap['D'] = GameEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = GameEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
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
		/*
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
		*/

		
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

		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
		
		
		GameEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (uint32_t y = 0; y < m_MapHeight; y++)
		{
			for (uint32_t x = 0; x < m_MapWidth; x++)
			{
				char tileType = s_MapTiles[x + y * s_MapWidth];
				GameEngine::Ref<GameEngine::SubTexture2D> texture;

				if (s_TextureMap.find(tileType) != s_TextureMap.end())
					texture = s_TextureMap[tileType];
				else 
					texture = s_TextureMap['D'];
				
				GameEngine::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f , m_MapHeight - y - m_MapHeight / 2.0f, 0.1f }, { 1.0f, 1.0f }, texture);
			}
		}

		//GameEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f, 0.1f }, { 1.0f, 1.0f }, m_TextureGrass);
		//GameEngine::Renderer2D::DrawQuad({ 0.0f, 1.0f, 0.1f }, { 1.0f, 1.0f }, m_TextureGrassBorder);
		GameEngine::Renderer2D::EndScene();
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
