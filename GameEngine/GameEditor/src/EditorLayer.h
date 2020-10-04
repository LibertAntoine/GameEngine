#pragma once

#include "GameEngine.h"
#include "Game/Scene/Scene.h"
#include "Panels/SceneHierarchyPanel.h"

namespace GameEngine {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_Shader;
		Ref<FrameBuffer> m_FrameBuffer;

		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		Ref<Scene> m_ActiveScene;

		bool m_PrimaryCamera = false;

		bool m_ViewportHovered = false;
		bool m_ViewportFocused = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		Ref<Texture2D> m_CheckerboardTexture;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };


		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}
