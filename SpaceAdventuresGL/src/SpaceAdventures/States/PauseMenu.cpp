#include "sapch.h"
#include "PauseMenu.h"
#include "Novaura/Novaura.h"
#include "SpaceAdventures/States/MainMenu.h"

namespace SpaceAdventures {


	PauseMenu::PauseMenu(Novaura::Window& window)	
	{
	
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
		m_ButtonList.emplace_back(std::make_unique<Button>("Assets/Textures/Buttons/ResumeButtonLight.png", ButtonType::Resume, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.20f)));
		m_ButtonList.emplace_back(std::make_unique<Button>("Assets/Textures/Buttons/MainMenuLight.png", ButtonType::MainMenu, glm::vec2(0.0f, -0.250f), glm::vec2(1.0f, 0.20f)));
		m_ButtonList.emplace_back(std::make_unique<Button>("Assets/Textures/Buttons/ExitButtonLight.png", ButtonType::Exit, glm::vec2(0.0f, -0.50f), glm::vec2(1.0f, 0.20f)));
	}

	void PauseMenu::HandleInput()
	{
		for (auto& button : m_ButtonList)
		{
			if (button->IsHovered())
			{
				switch (button->GetButtonType())
				{
				case ButtonType::Resume: m_StateMachine->PopState();
					
					break;
				case ButtonType::MainMenu: 						
					
					m_StateMachine->ClearPastStates();
					m_StateMachine->ReplaceCurrentState(std::make_unique<MainMenu>(m_Window, m_CameraController, m_StateMachine));
					
					break;
				case ButtonType::Exit: m_StateMachine->ShutDown();
					break;

				default:
					return;
				}
			}
		}
	}

	void PauseMenu::Update(float deltaTime)
	{
		for (auto& button : m_ButtonList)
		{
			button->Update();
		}

		Draw(deltaTime);
	}

	void PauseMenu::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
		//Novaura::Renderer::DrawRectangle(m_Title->GetRectangle(), m_Button->GetTextureFile());
		Novaura::Renderer::DrawRectangle(*m_Title, "Assets/Textures/Buttons/ResumeButtonLight.png");

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

