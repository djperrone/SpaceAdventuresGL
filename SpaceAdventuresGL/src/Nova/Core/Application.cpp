#include "sapch.h"
#include "Application.h"
#include "Nova/Renderer/Renderer.h"
#include <spdlog/spdlog.h>
#include "Nova/Renderer/Texture.h"
#include "Nova/TextureLoader/TextureLoader.h"
#include "glfwCallBackWrapper.h"

namespace test {

	glm::vec3 velocity(0.5f, 0.8f, 0.0f);
}

namespace Nova {

	Application::Application()
		: m_Context(1280.0f,720.0f), m_Camera(m_Context.GetWindow().Width, m_Context.GetWindow().Height), m_CameraController(m_Context.GetWindow().Width, m_Context.GetWindow().Height)
	{
		SetCallBackFunctions();
		Nova::Renderer::Init();
		
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(m_Context.GetWindow().Width/2.0f, m_Context.GetWindow().Height/2.0f), glm::vec2(64.0f, 64.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(300.0f / m_Context.GetWindow().Width * m_Context.GetWindow().AspectRatio, 500.0f / m_Context.GetWindow().Height * m_Context.GetWindow().AspectRatio), glm::vec2(16.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.5f, 0.5f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(300.0f / m_Context.GetWindow().Width * m_Context.GetWindow().AspectRatio, 500.0f / m_Context.GetWindow().Height * m_Context.GetWindow().AspectRatio), glm::vec2(16.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.5f, 0.5f));
		m_Rect = std::make_unique<Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.4f,0.4f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(640.0f / 1280.0f, 360.0f / 720.0f), glm::vec2(32.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(1.0f, 1.0f));
		//m_Rect = std::make_unique<Rectangle>(glm::vec2(500.0f, 300.0f), glm::vec2(32.0f, 32.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(1.0f,1.0f));
		m_Shader = std::make_unique<Shader>("Assets/Shaders/TextureShader.glsl");
		m_Shader->Bind();
		Texture tex = TextureLoader::LoadTexture("Assets/Textures/Spaceship.png");
		m_Shader->SetUniform1i("u_Texture", 0);
		tex.Bind();
	}

	void Application::Update()
	{
		ScreenSaver();
		float aspectRatio = m_Context.GetWindow().Width / m_Context.GetWindow().Height;

		BeginFrame();		
	
		Nova::Renderer::DrawRotatedRectangle(*m_Rect);
		

		EndFrame();
	}

	void Application::BeginFrame()
	{
		Nova::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Nova::Renderer::Clear();
		float currentFrame = glfwGetTime();
		m_DeltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;
		m_Context.PollEvents();
	}

	void Application::EndFrame()
	{
		m_Context.SwapBuffers();
	}

	void Application::WindowResizeCallBack(int width, int height)
	{
		glViewport(0, 0, width, height);
		GetWindow().Width = width;
		GetWindow().Height = height;
		
		m_CameraController.GetCamera().SetProjectionMatrix(width, height);
	}

	void Application::MouseScrollCallBack(double xoffset, double yoffset)
	{
		m_CameraController.ProcessMouseScroll(yoffset);
	}
	

	void Application::ScreenSaver()
	{
		
		
			float aspectRatio = m_Context.GetWindow().Width / m_Context.GetWindow().Height;

			BeginFrame();
			//m_Camera.SetProjectionMatrix(m_Context.GetWindow().Width, m_Context.GetWindow().Height);
			m_CameraController.Update(GetWindow(), m_DeltaTime);

			Renderer::BeginScene(*m_Shader, m_CameraController.GetCamera());
			//Renderer::BeginScene(*m_Shader, m_Camera);
			m_Rect->m_Rotation += 1.0f * m_DeltaTime;
			m_Rect->m_Position.y -= test::velocity.y * m_DeltaTime;
			m_Rect->m_Position.x -= test::velocity.x * m_DeltaTime;
			if (m_Rect->m_Position.y < -1.0f || m_Rect->m_Position.y > 1.0f)
			{
				test::velocity.y = -test::velocity.y;
			}
			if (m_Rect->m_Position.x < -aspectRatio || m_Rect->m_Position.x > aspectRatio)
			{
				test::velocity.x = -test::velocity.x;
			}

			Nova::Renderer::DrawRotatedRectangle(*m_Rect);


			EndFrame();
	}

	void Application::SetCallBackFunctions()
	{
	    GLFWCallbackWrapper::SetApplication(this);
	    //glfwSetCursorPosCallback(m_Window.Window, GLFWCallbackWrapper::MousePositionCallback);
	    glfwSetScrollCallback(GetWindow().Window, GLFWCallbackWrapper::MouseScrollCallBack);
	    glfwSetFramebufferSizeCallback(GetWindow().Window, GLFWCallbackWrapper::WindowResizeCallBack);
	}
}