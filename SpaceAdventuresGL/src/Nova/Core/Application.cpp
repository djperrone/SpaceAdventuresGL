#include "sapch.h"
#include "Application.h"
#include "Nova/Renderer/Renderer.h"
#include <spdlog/spdlog.h>
#include "Nova/Renderer/Texture.h"
#include "Nova/TextureLoader/TextureLoader.h"
#include "glfwCallBackWrapper.h"
#include "Nova/Input/InputHandler.h"

namespace test {

	glm::vec3 velocity(0.5f, 0.5f, 0.0f);
	
}

namespace Nova {

	Application::Application()
		: m_Context(1280.0f,720.0f), m_Camera(m_Context.GetWindow().Width, m_Context.GetWindow().Height), m_CameraController(m_Context.GetWindow().Width, m_Context.GetWindow().Height)
	{
		InputHandler::Init();
		SetCallBackFunctions();		
		InputHandler::BindAxisKeyEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });
		//InputHandler::BindAxisKeyEvent(GLFW_MOUSE_BUTTON_LEFT, []() {spdlog::info("test axis event mouse lc"); });
		//InputHandler::BindAxisKeyEvent(GLFW_KEY_U, []() {spdlog::info("test axis event U"); });
		InputHandler::BindActionKeyEvent(GLFW_PRESS, GLFW_KEY_U, []() {spdlog::info("test action event U"); });
		InputHandler::BindActionKeyEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, []() {spdlog::info("test action event MB lc"); });
		
		Nova::Renderer::Init();
		
		
		m_Rect = std::make_unique<Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.4f,0.4f));
		//InputHandler::BindAxisKeyEvent(GLFW_KEY_UP, [this, m_Rect = m_Rect.get(), m_DeltaTime = &m_DeltaTime]() { m_Rect->m_Position.y += test::velocity.y * *m_DeltaTime; spdlog::info("{0}, {1}", m_Rect->m_Position.x, m_Rect->m_Position.y); });
		//InputHandler::BindAxisKeyEvent(GLFW_KEY_DOWN, [this, m_Rect = &m_Rect, m_DeltaTime = &m_DeltaTime]() {m_Rect->get()->m_Position.y -= test::velocity.y * *m_DeltaTime; });
		//InputHandler::BindAxisKeyEvent(GLFW_KEY_LEFT, [this, m_Rect = &m_Rect, m_DeltaTime = &m_DeltaTime]() {m_Rect->get()->m_Position.x -= test::velocity.y * *m_DeltaTime; });
		//InputHandler::BindAxisKeyEvent(GLFW_KEY_RIGHT, [this, m_Rect = &m_Rect, m_DeltaTime = &m_DeltaTime]() {m_Rect->get()->m_Position.x += test::velocity.x * *m_DeltaTime; });

		
		
		m_Shader = std::make_unique<Shader>("Assets/Shaders/TextureShader.glsl");
		m_Shader->Bind();
		Texture tex = TextureLoader::LoadTexture("Assets/Textures/Spaceship.png");
		m_Shader->SetUniform1i("u_Texture", 0);
		tex.Bind();
	}

	void Application::Update()
	{
		//ScreenSaver();
		float aspectRatio = m_Context.GetWindow().Width / m_Context.GetWindow().Height;
		
		BeginFrame();		
		//spdlog::info("{0}, {1}", m_Rect->m_Position.x, m_Rect->m_Position.y);		
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
		m_CameraController.Update(GetWindow(), m_DeltaTime);
		Renderer::BeginScene(*m_Shader, m_CameraController.GetCamera());

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

	void Application::KeyboardCallback(int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			spdlog::info("space");
		}

		if (InputHandler::AxisKeyBindings.find(key) != InputHandler::AxisKeyBindings.end())
		{
			InputHandler::AxisKeyBindings[key].Execute();
		}

		if (InputHandler::ActionKeyBindings.find(action) != InputHandler::ActionKeyBindings.end())
		{
			if (InputHandler::ActionKeyBindings[action].find(key) != InputHandler::ActionKeyBindings[action].end())
			{
				InputHandler::ActionKeyBindings[action][key].Execute();
			}
		}		
	}	

	void Application::MouseButtonCallBack(int button, int action, int mods)
	{
		if (InputHandler::AxisKeyBindings.find(button) != InputHandler::AxisKeyBindings.end())
		{
			InputHandler::AxisKeyBindings[button].Execute();
		}

		if (InputHandler::ActionKeyBindings.find(action) != InputHandler::ActionKeyBindings.end())
		{
			if (InputHandler::ActionKeyBindings[action].find(button) != InputHandler::ActionKeyBindings[action].end())
			{
				InputHandler::ActionKeyBindings[action][button].Execute();
			}
		}
	}

	void Application::MousePositionCallBack(double positionX, double positionY)
	{
		//spdlog::info("{0}, {1}", positionX, positionY);
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
	    glfwSetCursorPosCallback(GetWindow().Window, GLFWCallbackWrapper::MousePositionCallBack);
	    glfwSetScrollCallback(GetWindow().Window, GLFWCallbackWrapper::MouseScrollCallBack);
	    glfwSetFramebufferSizeCallback(GetWindow().Window, GLFWCallbackWrapper::WindowResizeCallBack);
		glfwSetKeyCallback(GetWindow().Window, GLFWCallbackWrapper::KeyBoardCallback);
		glfwSetMouseButtonCallback(GetWindow().Window, GLFWCallbackWrapper::MouseButtonCallback);
	}
}