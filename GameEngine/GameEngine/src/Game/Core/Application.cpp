#include "gepch.h"
#include "Game/Core/Application.h"

#include "Game/Core/Input.h"

#include "Game/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace GameEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		
	{
		GE_PROFILE_FUNCTION();

		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));
		
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		GE_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::Run()
	{
		GE_PROFILE_FUNCTION();

		while (m_Running) 
		{
			GE_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); //Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {

				GE_PROFILE_SCOPE("LayerStack OnUpdate");

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);

			}

			m_ImGuiLayer->Begin();
			{
				GE_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->OnUpdate();

		}
	}


	void Application::PushLayer(Layer* layer)
	{
		GE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		GE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		GE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::OnWindowResize));


		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}