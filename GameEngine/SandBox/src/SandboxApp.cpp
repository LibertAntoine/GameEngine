#include <GameEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/Imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(GameEngine::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		GameEngine::Ref<GameEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GameEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		GameEngine::Ref<GameEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(GameEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(GameEngine::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		GameEngine::Ref<GameEngine::VertexBuffer> squareVB;
		squareVB.reset(GameEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		GameEngine::Ref<GameEngine::IndexBuffer> squareIb;
		squareIb.reset(GameEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIb);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";


		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = GameEngine::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;


			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";


		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader2 = GameEngine::Shader::Create("FlatColor", vertexSrc2, fragmentSrc2);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = GameEngine::Texture2D::Create("assets/textures/logo.png");
		m_Texture2 = GameEngine::Texture2D::Create("assets/textures/rgb.png");

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);



	}

	void OnUpdate(GameEngine::Timestep ts) override
	{
		//Renderer::BeginScene(camera, lights, enviroment);

		m_CameraController.OnUpdate(ts);


		if (GameEngine::Input::IsKeyPressed(GE_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts; // Delta Time

		else if (GameEngine::Input::IsKeyPressed(GE_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_I))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		else if (GameEngine::Input::IsKeyPressed(GE_KEY_K))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;




		GameEngine::RenderCommand::SetClearColor({ 1, 0.5, 0.5, 1 });
		GameEngine::RenderCommand::Clear();


		GameEngine::Renderer::BeginScene(m_CameraController.GetCamera());
		//GameEngine::Renderer2D::BeginScene(m_Camera);
		//GameEngine::Renderer2D::DrawQuad();
		// Create a batch renderer !! To improve performance in 2D;
		// Texture slots are limited to 32 slots by raw call.
		// We can use Texture Atlas for more.
		// Add Animation Sytem.
		// Improve our layout system.
		// Add Post Effects
		// Add Scripting System (BluePrints, LUA), ECS/CGO -> Decompose from component our game.


		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//GameEngine::MaterialRef material = new GameEngine::Material(m_Shader2);
		//GameEngine::MaterialInstanceRef mi = new GameEngine::MaterialInstance(material);

		//mi->Set("u_Color", redColor);
		//mi->SetTexture("u_AlbedoMap", texture);
		//squareMesh->SetMaterial(mi);

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int i = 0; i < 20; i++) {

				glm::vec3 pos(i * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				GameEngine::Renderer::Submit(/*mi, */m_Shader2, m_SquareVA, transform);

			}
		}
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind(0);
		GameEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		
		m_Texture2->Bind(0);
		GameEngine::Renderer::Submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		// Triangle
		//GameEngine::Renderer::Submit(/*mi, */m_Shader, m_VertexArray);
		
		
		GameEngine::Renderer::EndScene();

		// Renderer::Flush(); 
	}
	
	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}


	void OnEvent(GameEngine::Event & e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	GameEngine::ShaderLibrary m_ShaderLibrary;
	GameEngine::Ref<GameEngine::Shader> m_Shader;
	GameEngine::Ref<GameEngine::VertexArray> m_VertexArray;

	GameEngine::Ref<GameEngine::Shader> m_Shader2;
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;

	GameEngine::Ref<GameEngine::Texture2D> m_Texture, m_Texture2;

	GameEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public GameEngine::Application { // Define class child of the librairy gameEngine class
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox(); // Create new instance
}
