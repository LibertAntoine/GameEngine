#include <GameEngine.h>

// --- Entry Point ------------------
#include <Game/Core/EntryPoint.h>
// ----------------------------------

#include "EditorLayer.h"

namespace GameEngine {


	class GameEditor : public Application {
	public:
		GameEditor()
			: Application("Game Editor")
		{
			PushLayer(new EditorLayer());
		}

		~GameEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new GameEditor();
	}

}