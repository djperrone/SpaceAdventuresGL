#include "sapch.h"
#include "DeathScreen.h"
#include "Novaura/Novaura.h"
#include "SpaceAdventures/States/MainMenu.h"
#include "SpaceAdventures/States/Level.h"

#include "SpaceAdventures/Actors/Button.h"
#include "Novaura/Core/Application.h"


namespace SpaceAdventures {

	DeathScreen::DeathScreen()
	{
		m_Window = Novaura::InputHandler::GetCurrentWindow();
		m_CameraController = Novaura::Application::GetCameraController();
		m_StateMachine = Novaura::Application::GetStateMachine();
		OnEnter();
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

		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/ExitButtonLight.png", glm::vec3(0.0f, -0.50f, 0.0f), glm::vec3(1.0f, 0.20f, 0.0f),
			Novaura::Command([](){
				Novaura::Application::GetStateMachine()->ShutDown();	}
			)));

		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/MainMenuLight.png", glm::vec3(0.0f, -0.250f, 0.0f), glm::vec3(1.0f, 0.20f, 0.0f),
			Novaura::Command([]() {
				Novaura::Application::GetStateMachine()->ClearPastStates();
				Novaura::Application::GetStateMachine()->ReplaceCurrentState(std::make_unique<MainMenu>());	}
		)));

		m_ButtonList.emplace_back(std::make_unique<UI::ToggleButton>("Assets/Textures/Buttons/PlayAgainButtonLight.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.20f, 0.0f),
			Novaura::Command([]() {Novaura::Application::GetStateMachine()->ReplaceCurrentState(std::make_unique<Level>()); }
			)));
	}

	void DeathScreen::HandleInput()
	{
		for (auto& button : m_ButtonList)
		{
			if (button->IsHovered())
			{
				button->Execute();			
			}
		}
	}

	void DeathScreen::Update(float deltaTime)
	{
		for (auto& button : m_ButtonList)
		{
			button->Update();
		}		
	}

	void DeathScreen::Draw(float deltaTime)
	{
		Novaura::BatchRenderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::BatchRenderer::Clear();
		Novaura::BatchRenderer::BeginScene(m_CameraController->GetCamera());		
		Novaura::BatchRenderer::DrawRectangle(*m_Title, "Assets/Textures/Buttons/DeathScreenRed2.png");

		for (auto& button : m_ButtonList)
		{
			Novaura::BatchRenderer::DrawRectangle(button->GetRectangle(), button->GetTextureFile());
		}

		Novaura::BatchRenderer::EndScene();
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