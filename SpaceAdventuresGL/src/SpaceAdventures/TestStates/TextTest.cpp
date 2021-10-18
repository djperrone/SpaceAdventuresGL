#include "sapch.h"
#include "TextTest.h"

#include <glm/glm.hpp>
#include "Novaura/Renderer/Renderer.h"
#include <spdlog/spdlog.h>

#include "Novaura/Renderer/Texture.h"
#include "Novaura/Renderer/TextureLoader.h"
#include "Novaura/Renderer/TextLoader.h"
#include "Novaura/Input/InputHandler.h"

namespace SpaceAdventures {	

	TextTest::TextTest(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
	{
		m_Window = window;
		m_CameraController = cameraController;

		OnEnter();
	}

	void TextTest::OnEnter()
	{
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f));
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });
		Novaura::Texture tex = Novaura::TextureLoader::LoadTexture("Assets/Textures/Spaceship.png");
		/*Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_1, [m_Rect = &m_Rect, m_Window = &m_Window]()
			{
				if (Novaura::InputHandler::IsRectHovered(*m_Rect->get()))
				{
					spdlog::info("collision deteced!");
				}

			});*/
		Novaura::Renderer::Init();
		Novaura::TextLoader::Init();
	}


	void TextTest::HandleInput()
	{
	}
	namespace test {
		float velocity = 0.01f;
	}
	void TextTest::Update(float deltaTime)
	{
		m_CameraController->Update(GetWindow(), deltaTime);		
		float aspectRatio = m_Window->Width / m_Window->Height;

		
		

		
		m_Rect->GetPosition().x += test::velocity;
		if (m_Rect->GetPosition().x > aspectRatio)
		{
			test::velocity *= -1;
		}

		if (m_Rect->GetPosition().x < -aspectRatio)
		{
			test::velocity *= -1;
		}


		//Draw(deltaTime);		

	}

	void TextTest::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
		//Novaura::Renderer::DrawRotatedRectangle(*m_Rect);		
		//Novaura::Renderer::DrawOutlinedRectangle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),glm::vec4(0.1f,0.8f,0.1f,1.0f),"Assets/Textures/Spaceship.png");
		//Novaura::Renderer::DrawRectangle(glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		Novaura::Renderer::RenderText("Asdfsdfsdf", 0.0F, 0.0F, .0010f, glm::vec3(0.0f, 1.0f, 0.0f));
		Novaura::Renderer::RenderText( "This is sample text", 0.50f, .50f, .005f, glm::vec3(0.5, 0.8f, 0.2f));
		//Novaura::Renderer::RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
	}

	

	void TextTest::OnExit()
	{
	}

	void TextTest::Pause()
	{
	}

	void TextTest::Resume()
	{
	}
}
