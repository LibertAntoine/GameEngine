#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		// GE_INFO("ExampleLayer::Update");
	
		if (GameEngine::Input::IsKeyPressed(GE_KEY_TAB))
			GE_INFO("Tab key is pressed!");
	
	}

	void OnEvent(GameEngine::Event & event) override
	{
		// GE_INFO("{0}", event);
	}
};

class Sandbox : public GameEngine::Application { // Define class child of the librairy gameEngine class
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new GameEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox(); // Create new instance
}
