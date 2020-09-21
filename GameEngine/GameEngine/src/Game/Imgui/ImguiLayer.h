#pragma once

#include "Game/Core/Layer.h"

#include "Game/Events/ApplicationEvent.h"
#include "Game/Events/KeyEvent.h"
#include "Game/Events/MouseEvent.h"

namespace GameEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		/*
		virtual void OnUpdate() override;
		void OnEvent(Event& event);
	private:
		
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		*/
	private:
		float m_Time = 0.0f;
	};

}