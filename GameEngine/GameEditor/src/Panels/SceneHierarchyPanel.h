#pragma once

#include "Game/Scene/Scene.h"
#include "Game/Core/Log.h"
#include "Game/Core/Base.h"
#include "Game/Scene/Entity.h"

namespace GameEngine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

	};

}