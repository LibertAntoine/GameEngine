#include "gepch.h"
#include "Game/Core/Window.h"

#ifdef GE_PLATFORM_WINDOWS
	#include "Platform/Window/WindowsWindow.h"
#endif

namespace GameEngine
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef GE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		GE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}