#pragma once

#include "Game/Core/Base.h"
#include "Game/Core/KeyCodes.h"
#include "Game/Core/MouseCodes.h"

namespace GameEngine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}