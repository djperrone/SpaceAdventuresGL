#include "sapch.h"
#include "Application.h"
#include "Renderer/Renderer.h"


Application::Application()
	: m_Context()
{
	Core::Renderer::Init();

	m_Rect = std::make_unique<Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f));
	m_Shader = std::make_unique<Shader>("Assets/Shaders/RectangleShader.glsl");

}

void Application::Update()
{
	BeginFrame();

	m_Shader->Bind();
	m_Rect->Draw(*m_Shader);


	EndFrame();
}

void Application::BeginFrame()
{
	Core::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	Core::Renderer::Clear();

	m_Context.PollEvents();
}

void Application::EndFrame()
{
	m_Context.SwapBuffers();
}
