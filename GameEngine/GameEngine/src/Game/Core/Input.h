#pragma once

#include "Game/Core/Base.h"
#include "Game/Core/KeyCodes.h"
#include "Game/Core/MouseCodes.h"

namespace GameEngine {

	class Input
	{
	public:
		virtual ~Input() = default;

		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static Ref<Input> Create();

	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	
		
	private:
		static Ref<Input> s_Instance;
	
	};

}