#include "sapch.h"
#include "DeathScreen.h"
#include "Novaura/Novaura.h"
#include "SpaceAdventures/States/MainMenu.h"
#include "SpaceAdventures/States/Level.h"


namespace SpaceAdventures {

	DeathScreen::DeathScreen(Novaura::Window& window)		
	{
		
	}

	DeathScreen::DeathScreen(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine)
	{
		m_Window = window;
		m_CameraController = cameraController;
		m_StateMachine = stateMachine;
		OnEnter();
	}

	void DeathScreen::OnEnter()
	{
		m_InputController = Novaura::InputHandler::CreateNewInputController();
		Novaura::InputHandler::SetCurrentController(m_InputController);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, &DeathScreen::HandleInput, this);

		m_Title = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.5f), glm::vec2(2.0f, 0.40f));
		m_ButtonList.emplace_back(std::make_unique<Button>("Assets/Textures/Buttons/PlayAgainButtonLight.png", ButtonType::Play, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.20f)));
		m_ButtonList.emplace_back(std::make_unique<Button>("Assets/Textures/Buttons/MainMenuLight.png", ButtonType::MainMenu, glm::vec2(0.0f, -0.250f), glm::vec2(1.0f, 0.20f)));

		m_ButtonList.emplace_back(std::make_unique<Button>("Assets/Textures/Buttons/ExitButtonLight.png", ButtonType::Exit, glm::vec2(0.0f, -0.50f), glm::vec2(1.0f, 0.20f)));
	}

	void DeathScreen::HandleInput()
	{
		for (auto& button : m_ButtonList)
		{
			if (button->IsHovered())
			{
				switch (button->GetButtonType())
				{
				case ButtonType::Play: m_StateMachine->ReplaceCurrentState(std::make_unique<Level>(m_Window, m_CameraController, m_StateMachine));

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

	void DeathScreen::Update(float deltaTime)
	{
		for (auto& button : m_ButtonList)
		{
			button->Update(deltaTime);
		}

		//Draw(deltaTime);
	}

	void DeathScreen::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
		//Novaura::Renderer::DrawRectangle(m_Title->GetRectangle(), m_Button->GetTextureFile());
		Novaura::Renderer::DrawRectangle(*m_Title, "Assets/Textures/Buttons/DeathScreenRed2.png");

		for (auto& button : m_ButtonList)
		{
			Novaura::Renderer::DrawRectangle(button->GetRectangle(), button->GetTextureFile());
		}
	}



	void DeathScreen::OnExit()
	{
	}

	void DeathScreen::Pause()
	{
	}

	void DeathScreen::Resume()
	{
	}
}