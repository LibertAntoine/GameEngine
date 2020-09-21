#include "gepch.h"
#include "Game/Core/Input.h"

#ifdef GE_PLATFORM_WINDOWS
	#include "Platform/Window/WindowsInput.h"
#endif

namespace GameEngine {

	Ref<Input> Input::s_Instance = Input::Create();

	Ref<Input> Input::Create()
	{
		#ifdef GE_PLATFORM_WINDOWS
				return CreateRef<WindowsInput>();
		#else
				GE_CORE_ASSERT(false, "Unknown platform!");
				return nullptr;
		#endif
	}
}