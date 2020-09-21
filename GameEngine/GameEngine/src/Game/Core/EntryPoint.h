#pragma once
#include "Game/Core/Base.h"


#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{
	GameEngine::Log::Init();

	GE_PROFILE_BEGIN_SESSION("Startup", "GEProfile-Startup.json");
	auto app = GameEngine::CreateApplication();
	GE_PROFILE_END_SESSION();

	GE_PROFILE_BEGIN_SESSION("Runtime", "GEProfile-Runtime.json");
	app->Run();
	GE_PROFILE_END_SESSION();

	GE_PROFILE_BEGIN_SESSION("Shutdown", "GEProfile-Shutdown.json");
	delete app;
	GE_PROFILE_END_SESSION();
}

#endif