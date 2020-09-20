#pragma once

#include "GameEngine.h"
#include "ParticuleSystem.h"

class Sandbox2D : public GameEngine::Layer
{
public:
	Sandbox2D();
	 virtual ~Sandbox2D() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(GameEngine::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(GameEngine::Event& e) override;
private:
	GameEngine::OrthographicCameraController m_CameraController;
	
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;
	GameEngine::Ref<GameEngine::Shader> m_Shader;
	
	GameEngine::Ref<GameEngine::Texture2D> m_CheckerboardTexture;
	GameEngine::Ref<GameEngine::Texture2D> m_SpriteSheet;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;


	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

};
