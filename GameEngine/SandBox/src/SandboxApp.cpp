#include <GameEngine.h>

class Sandbox : public GameEngine::Application { // Define class child of the librairy gameEngine class
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox(); // Create new instance
}
