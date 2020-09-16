#pragma once

#include "Game/Renderer/OrthographicCamera.h"
#include "Game/Core/Timestep.h"

#include "Game/Events/ApplicationEvent.h"
#include "Game/Events/MouseEvent.h"

namespace GameEngine {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }
	
		inline void SetZoomLevel(float level) { m_ZoomLevel = level; }
		inline float GetZoomLevel() const { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowRezised(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation = false;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;
	};
}
