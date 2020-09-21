#include <GameEngine.h>

// --- Entry Point ------------------
#include <Game/Core/EntryPoint.h>
// ----------------------------------

#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public GameEngine::Application { // Define class child of the librairy gameEngine class
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox(); // Create new instance
}
