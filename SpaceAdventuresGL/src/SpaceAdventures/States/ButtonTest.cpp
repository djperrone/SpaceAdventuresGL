#include "sapch.h"
#include "ButtonTest.h"

#include <glm/glm.hpp>
#include "Novaura/Renderer/Renderer.h"
#include "Novaura/Renderer/BatchRenderer.h"
#include <spdlog/spdlog.h>

#include "Novaura/Renderer/Texture.h"
#include "Novaura/Renderer/TextureLoader.h"
#include "Novaura/Renderer/TextLoader.h"
#include "Novaura/Input/InputHandler.h"

#include "GUI/GUI.h"

namespace SpaceAdventures {	

	ButtonTest::ButtonTest(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
	{
		m_Window = window;
		m_CameraController = cameraController;

		OnEnter();
	}

	void ButtonTest::OnEnter()
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

		GUI::Interface::AddToggleButton("PLAY", glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,0.2f,0.0f), glm::vec4(0.9f,0.9f,0.9f,1.0f), glm::vec4(0.2f,0.2f,0.2,1.0f),
			Novaura::Command([]() {spdlog::info("this is a test"); }));
		Novaura::Renderer::Init();
		Novaura::TextLoader::Init();
	}


	void ButtonTest::HandleInput()
	{
	}

	void ButtonTest::Update(float deltaTime)
	{
		m_CameraController->Update(GetWindow(), deltaTime);		
		float aspectRatio = m_Window->Width / m_Window->Height;
		
		
		GUI::Interface::Update();

		//Draw(deltaTime);		

	}

	void ButtonTest::Draw(float deltaTime)
	{
		Novaura::BatchRenderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::BatchRenderer::Clear();
		Novaura::BatchRenderer::BeginScene(m_CameraController->GetCamera());
		//Novaura::Renderer::DrawRotatedRectangle(*m_Rect);		
		//Novaura::Renderer::DrawOutlinedRectangle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),glm::vec4(0.1f,0.8f,0.1f,1.0f),"Assets/Textures/Spaceship.png");
		//Novaura::Renderer::DrawRectangle(glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		//Novaura::Renderer::RenderText("Asdfsdfsdf", 0.0F, 0.0F, .0010f, glm::vec3(0.0f, 1.0f, 0.0f));
		//Novaura::Renderer::RenderText( "This is sample text", 0.50f, .50f, .005f, glm::vec3(0.5, 0.8f, 0.2f));
		//Novaura::Renderer::RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
		Novaura::BatchRenderer::DrawRectangle(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.25f, 0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		//Novaura::BatchRenderer::EndScene();
		GUI::Interface::Draw();

	}

	

	void ButtonTest::OnExit()
	{
	}

	void ButtonTest::Pause()
	{
	}

	void ButtonTest::Resume()
	{
	}
}
