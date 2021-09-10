#include "sapch.h"
#include "PauseMenu.h"
#include "Novaura/Novaura.h"
#include "SpaceAdventures/States/MainMenu.h"
#include "Novaura/Core/Application.h"

namespace SpaceAdventures {


	PauseMenu::PauseMenu()	
	{		
		m_Window = Novaura::InputHandler::GetCurrentWindow();
		m_CameraController = Novaura::Application::GetCameraController();
		m_StateMachine = Novaura::Application::GetStateMachine();
		OnEnter();		
	}

	PauseMenu::PauseMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine)
	{
		m_Window = window;
		m_CameraController = cameraController;
		m_StateMachine = stateMachine;

		OnEnter();
	}

	void PauseMenu::OnEnter()
	{
		m_InputController = Novaura::InputHandler::CreateNewInputController();
		Novaura::InputHandler::SetCurrentController(m_InputController);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, &PauseMenu::HandleInput, this);

		m_Title = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.5f), glm::vec2(2.0f, 0.40f));
		
		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/ExitButtonLight.png", glm::vec3(0.0f, -0.50f, 0.0f), glm::vec3(1.0f, 0.20f, 0.0f),
			Novaura::Command([]() {
				Novaura::Application::GetStateMachine()->ShutDown();	}
		)));

		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/MainMenuLight.png", glm::vec3(0.0f, -0.250f, 0.0f), glm::vec3(1.0f, 0.20f, 0.0f),
			Novaura::Command([]() {
				Novaura::Application::GetStateMachine()->ClearPastStates();
				Novaura::Application::GetStateMachine()->ReplaceCurrentState(std::make_unique<MainMenu>());	}
		)));

		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/ResumeButtonLight.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.20f, 0.0f),
			Novaura::Command([]() {Novaura::Application::GetStateMachine()->PopState(); }
		)));		
		
		m_IsPaused = true;
	}

	void PauseMenu::HandleInput()
	{
		for (auto& button : m_ButtonList)
		{
			if (button->IsHovered())
			{
				button->Execute();				
			}
		}
	}

	void PauseMenu::Update(float deltaTime)
	{
		for (auto& button : m_ButtonList)
		{
			button->Update();
		}

	
	}

	void PauseMenu::Draw(float deltaTime)
	{
		//Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		//Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
		//Novaura::Renderer::DrawRectangle(m_Title->GetRectangle(), m_Button->GetTextureFile());
		Novaura::Renderer::DrawRectangle(*m_Title, "Assets/Textures/Buttons/TitleLight.png");

		for (auto& button : m_ButtonList)
		{
			Novaura::Renderer::DrawRectangle(button->GetRectangle(), button->GetTextureFile());
		}
	}	

	void PauseMenu::OnExit()
	{
	}

	void PauseMenu::Pause()
	{
	}

	void PauseMenu::Resume()
	{
	}
}

