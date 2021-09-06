#include "sapch.h"
#include "Level.h"
#include "Novaura/Novaura.h"
#include "SpaceAdventures/States/PauseMenu.h"

namespace SpaceAdventures {


	Level::Level(Novaura::Window& window)		
	{
		
	}

	Level::Level(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine)
	{
		m_Window = window;
		m_CameraController = cameraController;
		m_StateMachine = stateMachine;
		OnEnter();
	}

	void Level::HandleInput()
	{
	}

	void Level::Update(float deltaTime)
	{		
		
		Draw(deltaTime);
	}

	void Level::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.5f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
	}

	void Level::OnEnter()
	{
		m_InputController = Novaura::InputHandler::CreateNewInputController();
		Novaura::InputHandler::SetCurrentController(m_InputController);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_KEY_ESCAPE, &Level::Pause, this);

	}

	void Level::OnExit()
	{
	}

	void Level::Pause()
	{
		m_StateMachine->PushState(std::make_unique<PauseMenu>(m_Window, m_CameraController, m_StateMachine));
	}

	void Level::Resume()
	{
		Novaura::InputHandler::SetCurrentController(m_InputController);
	}
}
