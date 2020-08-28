#pragma once

#include "Core.h"

namespace GameEngine {
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be define in client.
	Application* CreateApplication();
};
