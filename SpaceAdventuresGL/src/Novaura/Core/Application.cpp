#include "sapch.h"
#include "Application.h"
#include "Novaura/Renderer/Renderer.h"
#include <spdlog/spdlog.h>
#include "Novaura/Renderer/Texture.h"
#include "Novaura/TextureLoader/TextureLoader.h"
#include "glfwCallBackWrapper.h"
#include "Novaura/Input/InputHandler.h"

namespace test {

	glm::vec3 velocity(0.5f, 0.5f, 0.0f);
	
}

namespace Novaura {

	Application::Application()
		: m_Context(1280.0f,720.0f), m_CameraController(m_Context.GetWindow().Width, m_Context.GetWindow().Height)
	{		
		InputHandler::Init();
		Novaura::Renderer::Init();

		InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });	
		InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_KEY_U, []() {spdlog::info("test action event U"); });
		InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, []() {spdlog::info("test action event MB lc"); });
		SetCallBackFunctions();		
		
		
		m_Rect = std::make_unique<Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.4f,0.4f));
		

		
		
		m_Shader = std::make_unique<Shader>("Assets/Shaders/TextureShader.glsl");
		m_Shader->Bind();
		Texture tex = TextureLoader::LoadTexture("Assets/Textures/Spaceship.png");
		m_Shader->SetUniform1i("u_Texture", 0);
		tex.Bind();
	}

	Application::~Application()
	{
		InputHandler::ShutDown();

	}

	void Application::Update()
	{
		float currentFrame = glfwGetTime();
		m_DeltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;
		m_Context.PollEvents();
		m_CameraController.Update(GetWindow(), m_DeltaTime);

		m_StateMachine.GetCurrentState().Update(m_DeltaTime);
		spdlog::info("application update nova");
		//ScreenSaver();
		//float aspectRatio = m_Context.GetWindow().Width / m_Context.GetWindow().Height;
		
		//BeginFrame();		
		//spdlog::info("{0}, {1}", m_Rect->m_Position.x, m_Rect->m_Position.y);		
		//Novaura::Renderer::DrawRotatedRectangle(*m_Rect);		



		m_Context.SwapBuffers();
		//EndFrame();
	}

	void Application::BeginFrame()
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
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
		InputController controller = InputHandler::GetCurrentController();

		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			spdlog::info("space");
		}

		if (controller.GetAxisInputBindings().find(key) != controller.GetAxisInputBindings().end())
		{
			controller.GetAxisInputBindings()[key].Execute();
		}

		if (controller.GetActionInputBindings().find(action) != controller.GetActionInputBindings().end())
		{
			if (controller.GetActionInputBindings()[action].find(key) != controller.GetActionInputBindings()[action].end())
			{
				controller.GetActionInputBindings()[action][key].Execute();
			}
		}		
	}	

	void Application::MouseButtonCallBack(int button, int action, int mods)
	{
		InputController controller = InputHandler::GetCurrentController();

		if (controller.GetAxisInputBindings().find(button) != controller.GetAxisInputBindings().end())
		{
			controller.GetAxisInputBindings()[button].Execute();
		}

		if (controller.GetActionInputBindings().find(action) != controller.GetActionInputBindings().end())
		{
			if (controller.GetActionInputBindings()[action].find(button) != controller.GetActionInputBindings()[action].end())
			{
				controller.GetActionInputBindings()[action][button].Execute();
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

			Novaura::Renderer::DrawRotatedRectangle(*m_Rect);


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