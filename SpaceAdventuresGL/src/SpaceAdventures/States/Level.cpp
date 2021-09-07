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
		Novaura::Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());

		//if(m_ObjectManager->GetPlayer().IsReloading())
		//float size = m_ObjectManager->GetPlayer().GetGun().GetMagazineSize();

		float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;
		
		float quantity = m_ObjectManager->GetPlayer().GetGun().GetMagazineSize() - m_ObjectManager->GetPlayer().GetGun().GetBulletsUsed();

	
		glm::vec3 scale = glm::vec3(quantity / 10.0f, 0.1f, 0.0f);
		glm::vec3 pos = glm::vec3(aspectRatio * 0.7f, aspectRatio * -0.5f, 0.0f);


		

		if (m_ObjectManager->GetPlayer().GetGun().IsReloading())
		{
			//Novaura::Renderer::DrawRectangle(pos, scale, glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), "Assets/Textures/WoodenBox.png", m_ObjectManager->GetPlayer().GetGun().GetMagazineSize());
			//Novaura::Renderer::DrawRectangle(pos, scale, glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), "Assets/Textures/WoodenBox.png", 1.0f);
			//Novaura::Renderer::DrawRectangle(m_ObjectManager->GetPlayer().GetRectangle(), "Assets/Textures/WoodenBox.png");

			m_CurrentTime = glfwGetTime();
			if (m_CurrentTime - m_PreviousTime >= 0.5)
			{
				//Novaura::Renderer::DrawRectangle(pos, glm::vec3(1.0f, 0.1f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), "Assets/Textures/ReloadIcon.png", 1.0f);
				Novaura::Renderer::DrawRectangle(pos, glm::vec3(1.0f,0.1f,0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), "Assets/Textures/ReloadIcon.png", m_ObjectManager->GetPlayer().GetGun().GetMagazineSize());
				m_PreviousTime = m_CurrentTime;
			}

		}
		else
		{
			Novaura::Renderer::DrawRectangle(pos, scale, glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), "Assets/Textures/ReloadIcon.png", quantity);

		}
		for (auto& projectile : m_ObjectManager->GetProjectileList())
		{
			Novaura::Renderer::DrawRotatedRectangle(projectile->GetRectangle(), projectile->GetTextureFile());
		}

		for (auto& asteroid : m_ObjectManager->GetAsteroidList())
		{
			Novaura::Renderer::DrawRectangle(asteroid->GetRectangle(), asteroid->GetTextureFile());
		}
		for (auto& ship : m_ObjectManager->GetShipList())
		{
			Novaura::Renderer::DrawRotatedRectangle(ship->GetRectangle(), ship->GetTextureFile());
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
