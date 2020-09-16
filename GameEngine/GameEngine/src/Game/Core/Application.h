#pragma once

#include "gepch.h"

#include "Game/Core/Core.h"
#include "Game/Core/Window.h"

#include "Game/Core/LayerStack.h"
#include "Game/Events/Event.h"
#include "Game/Events/ApplicationEvent.h"

#include "Game/Core/Timestep.h"

#include "Game/Imgui/ImguiLayer.h"



namespace GameEngine {
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private: 
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool m_Running = true;
		bool m_Minimized = false;

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime;
	private:
		static Application* s_Instance;
	};

	// To be define in client.
	Application* CreateApplication();
};
