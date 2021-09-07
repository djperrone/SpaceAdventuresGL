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
		m_ObjectManager->Update(deltaTime);
		Draw(deltaTime);
	}

	void Level::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.4f, 0.2f, 0.0f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());

		for (auto& asteroid : m_ObjectManager->GetAsteroidList())
		{
			Novaura::Renderer::DrawRectangle(asteroid->GetRectangle(), asteroid->GetTextureFile());
		}
		for (auto& ship : m_ObjectManager->GetShipList())
		{
			Novaura::Renderer::DrawRectangle(ship->GetRectangle(), ship->GetTextureFile());
		}
		for (auto& projectile : m_ObjectManager->GetProjectileList())
		{
			Novaura::Renderer::DrawRectangle(projectile->GetRectangle(), projectile->GetTextureFile());
		}
		/*auto asteroid = std::make_unique<Asteroid>(0.0f, 0.0f);
		Novaura::Renderer::DrawRectangle(asteroid->GetRectangle(), asteroid->GetTextureFile());*/

	}

	void Level::OnEnter()
	{
		m_InputController = Novaura::InputHandler::CreateNewInputController();
		Novaura::InputHandler::SetCurrentController(m_InputController);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_KEY_ESCAPE, &Level::Pause, this);

		m_ObjectManager = std::make_unique<ObjectManager>();
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
