#include "sapch.h"

#include "MainMenu.h"
#include "SpaceAdventures/Actors/Button.h"
#include "Novaura/Novaura.h"
#include "Novaura/Core/Application.h"

#include "Level.h"
#include "Novaura/Primitives/Rectangle.h"


namespace SpaceAdventures {

	MainMenu::MainMenu()		
	{
		m_Window = Novaura::InputHandler::GetCurrentWindow();
		m_CameraController = Novaura::Application::GetCameraController();
		m_StateMachine = Novaura::Application::GetStateMachine();
		OnEnter();
	}

	MainMenu::MainMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine)
	{
		m_Window = window;
		m_CameraController = cameraController;	
		m_StateMachine = stateMachine;
		OnEnter();
	}

	void MainMenu::OnEnter()
	{
		m_InputController = Novaura::InputHandler::CreateNewInputController();
		Novaura::InputHandler::SetCurrentController(m_InputController);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, &MainMenu::HandleInput, this);

		m_Title = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.5f), glm::vec2(2.0f, 0.40f));		
		
		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/PlayButtonLight.png", std::move(glm::vec3{ 0.0f, 0.0f,0.0f }), std::move(glm::vec3{ 1.0f, 0.2f, 0.0f }),
			Novaura::Command([]() {Novaura::Application::GetStateMachine()->ReplaceCurrentState(std::make_unique<Level>()); }
			)));

		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/ExitButtonLight.png", std::move(glm::vec3{ 0.0f, -0.25f,0.0f }), std::move(glm::vec3{ 1.0f, 0.2f, 0.0f }),
			Novaura::Command([]() {Novaura::Application::GetStateMachine()->ShutDown(); }	)));
	}

	void MainMenu::Update(float deltaTime)
	{
		for (auto& button : m_ButtonList)
		{
			button->Update();
		}		
	}

	void MainMenu::Draw(float deltaTime)
	{
		Novaura::BatchRenderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::BatchRenderer::Clear();
		Novaura::BatchRenderer::BeginScene(m_CameraController->GetCamera());		
		Novaura::BatchRenderer::DrawRectangle(*m_Title, "Assets/Textures/Buttons/TitleLight.png");

		for (auto& button : m_ButtonList)
		{
			Novaura::BatchRenderer::DrawRectangle(button->GetRectangle(), button->GetTextureFile());
		}
		Novaura::BatchRenderer::EndScene();
	}

	void MainMenu::HandleInput()
	{
		for (auto& button : m_ButtonList)
		{
			if (button->IsHovered())
			{
				button->Execute();				
			}
		}
	}	

	void MainMenu::OnExit()
	{
	}

	void MainMenu::Pause()
	{
	}

	void MainMenu::Resume()
	{
	}

}
