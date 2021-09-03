#include "sapch.h"
#include "Application.h"
#include "Nova/Renderer/Renderer.h"

namespace Nova {

	Application::Application()
		: m_Context(1280.0f, 720.0f), m_Camera(m_Context.GetWindow().Width, m_Context.GetWindow().Height)
	{
		Nova::Renderer::Init();

		m_Rect = std::make_unique<Rectangle>(glm::vec2(500.0f, 500.0f), glm::vec2(64.0f, 64.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f));
		
		m_Shader = std::make_unique<Shader>("Assets/Shaders/BasicColorShader.glsl");
	}
	
	void Application::Update()
	{
		
		BeginFrame();
		Renderer::BeginScene(*m_Shader, m_Camera);
		//m_Shader->Bind();
		Nova::Renderer::Draw(*m_Rect);
		//m_Rect->Draw(*m_Shader);


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