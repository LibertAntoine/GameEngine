#pragma once

#include "gepch.h"

#include "Game/Core/Base.h"
#include "Game/Core/Window.h"

#include "Game/Core/LayerStack.h"
#include "Game/Events/Event.h"
#include "Game/Events/ApplicationEvent.h"

#include "Game/Core/Timestep.h"

#include "Game/Imgui/ImguiLayer.h"

int main(int argc, char** argv);

namespace GameEngine {
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();



		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private: 
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool m_Running = true;
		bool m_Minimized = false;

		Ref<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastFrameTime;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be define in client.
	Application* CreateApplication();
};
