#include "sapch.h"
#include "Application.h"
#include "Nova/Renderer/Renderer.h"
#include <spdlog/spdlog.h>
namespace Nova {

	Application::Application()
		: m_Context(1280.0f,720.0f), m_Camera(m_Context.GetWindow().Width, m_Context.GetWindow().Height)
	{
		Nova::Renderer::Init();

		//m_Rect = std::make_unique<Rectangle>(glm::vec2(m_Context.GetWindow().Width/2.0f, m_Context.GetWindow().Height/2.0f), glm::vec2(64.0f, 64.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(300.0f / m_Context.GetWindow().Width * m_Context.GetWindow().AspectRatio, 500.0f / m_Context.GetWindow().Height * m_Context.GetWindow().AspectRatio), glm::vec2(16.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.5f, 0.5f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(300.0f / m_Context.GetWindow().Width * m_Context.GetWindow().AspectRatio, 500.0f / m_Context.GetWindow().Height * m_Context.GetWindow().AspectRatio), glm::vec2(16.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.5f, 0.5f));
		m_Rect = std::make_unique<Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(1.0f,1.0f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(640.0f / 1280.0f, 360.0f / 720.0f), glm::vec2(32.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(1.0f, 1.0f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(500.0f, 300.0f), glm::vec2(32.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(1.0f,1.0f));

		m_Shader = std::make_unique<Shader>("Assets/Shaders/BasicColorShader.glsl");
	}
	namespace test { int count = 0; }
	void Application::Update()
	{
		float aspectRatio = m_Context.GetWindow().Width / m_Context.GetWindow().Height;

		BeginFrame();
		m_Camera.SetProjectionMatrix(m_Context.GetWindow().Width, m_Context.GetWindow().Height);
		
		Renderer::BeginScene(*m_Shader, m_Camera);

		//m_Rect->m_Position.y -= 0.008;
		//if (m_Rect->m_Position.y < -1.0f)
		//{
		//	m_Rect->m_Position.y = aspectRatio;
		//}
		//double xpos, ypos;
		//glfwGetCursorPos(m_Context.GetWindow().Window, &xpos, &ypos);
		////m_Shader->Bind();
		//spdlog::info("{0}, {1}", xpos, ypos);
		Nova::Renderer::Draw(*m_Rect);
		
		

		EndFrame();
	}

	void Application::BeginFrame()
	{
		Nova::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Nova::Renderer::Clear();

		m_Context.PollEvents();
	}

	void Application::EndFrame()
	{
		m_Context.SwapBuffers();
	}
}