#include "sapch.h"
#include "Level.h"

#include "Novaura/Novaura.h"
#include "Novaura/Collision/Collision.h"
#include "SpaceAdventures/States/PauseMenu.h"
#include "SpaceAdventures/States/DeathScreen.h"
#include "Novaura/Core/Application.h"


namespace SpaceAdventures {
	

	Level::Level()
	{
		m_Window = Novaura::InputHandler::GetCurrentWindow();
		m_CameraController = Novaura::Application::GetCameraController();
		m_StateMachine = Novaura::Application::GetStateMachine();
		OnEnter();
	}
	
	Level::Level(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine)
	{
		m_Window = window;
		m_CameraController = cameraController;
		m_StateMachine = stateMachine;
		OnEnter();
	}

	void Level::OnEnter()
	{
		glfwSetInputMode(Novaura::InputHandler::GetCurrentWindow()->Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		m_InputController = Novaura::InputHandler::CreateNewInputController();
		Novaura::InputHandler::SetCurrentController(m_InputController);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_KEY_ESCAPE, &Level::Pause, this);

		m_ObjectManager = std::make_unique<ObjectManager>();
		m_Cursor = std::make_unique<CursorTarget>();

		// player controlls setup in player class
	}

	void Level::HandleInput()
	{
	}

	void Level::Update(float deltaTime)
	{		
		if (!m_ObjectManager->GetPlayer().IsAlive())
		{
			if (firstTimeDead)
			{
				//m_DeadPlayer = std::make_uni
				startTime = glfwGetTime();
				firstTimeDead = false;
				return;
			}
			else
			{
				double currentTime = glfwGetTime();
				if (currentTime - startTime >= totalEventTime)
				{
					m_StateMachine->ReplaceCurrentState(std::make_unique<DeathScreen>(m_Window, m_CameraController, m_StateMachine));
					return;

				}
				else
				{
					return;
				}
			}
			
			 //return;
		}
		//previousTime = currentTime;

		m_Cursor->Update(deltaTime);
		m_ObjectManager->Update(deltaTime);
		m_CameraController->Update(*Novaura::InputHandler::GetCurrentWindow(),deltaTime);		
	}

	void Level::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());		

		float width = Novaura::InputHandler::GetCurrentWindow()->Width;
		float height = Novaura::InputHandler::GetCurrentWindow()->Height;
		float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;		
		
		// healthbar
		glm::vec3 healthScale = glm::vec3(glm::mix(0.0f,0.25f,m_ObjectManager->GetPlayer().GetHealth()), 0.15f, 0.0f);
		float currentHealth = m_ObjectManager->GetPlayer().GetHealth();
		float maxHealth = m_ObjectManager->GetPlayer().GetMaxHealth();
		glm::vec4 healthColor = glm::vec4((maxHealth - currentHealth) / maxHealth, currentHealth / maxHealth, 0.0f, 1.0f);

		/*glm::vec3 healthPos = aspectRatio > 0 ? glm::vec3(-aspectRatio + healthScale.x * 0.5f, -1.0f + healthScale.y, 0.0f) :
			glm::vec3(-1.0f + healthScale.x * 0.5f, -1.0f + healthScale.y, 0.0f);*/

		glm::vec3 healthPos = glm::vec3(-aspectRatio + healthScale.x * 0.5f, -1.0f + healthScale.y, 0.0f);
		
		Novaura::Renderer::DrawRectangle(healthPos, healthScale, healthColor);

		// reload icon

		glm::vec2 quantity = glm::vec2(1.0f,1.0f);
		quantity.x = static_cast<float>(m_ObjectManager->GetPlayer().GetGun().GetMagazineSize() - m_ObjectManager->GetPlayer().GetGun().GetBulletsUsed());
		glm::vec3 scale = glm::vec3(quantity.x / 10.0f, 0.1f, 0.0f);
		glm::vec3 pos = glm::vec3(aspectRatio - scale.x * 0.5f, -1.0f + scale.y, 0.0f);
		if (m_ObjectManager->GetPlayer().GetGun().IsReloading())
		{						
			scale = glm::vec3(m_ObjectManager->GetPlayer().GetGun().GetBulletsUsed()/10.0f, 0.1f, 0.0f);
			pos = glm::vec3(aspectRatio - scale.x * 0.5f, -1.0f + scale.y, 0.0f);
			Novaura::Renderer::DrawRectangle(pos, scale, glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), "Assets/Textures/ReloadIcon.png", glm::vec2(m_ObjectManager->GetPlayer().GetGun().GetBulletsUsed(), 1.0f));		
		}
		else
		{
			Novaura::Renderer::DrawRectangle(pos, scale, glm::vec4(1.0f, 1.0f, 1.0f, 0.75f), "Assets/Textures/ReloadIcon.png", quantity);
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
		m_Cursor->CheckForCollision(m_ObjectManager->GetShipList());


		// mouse cursor target
		Novaura::Renderer::DrawRectangle(m_Cursor->GetRectangle(), m_Cursor->GetTextureFile());

		if (!m_ObjectManager->GetPlayer().IsAlive())
		{

		}
	}

	

	void Level::OnExit()
	{




		glfwSetInputMode(Novaura::InputHandler::GetCurrentWindow()->Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Level::Pause()
	{
		glfwSetInputMode(Novaura::InputHandler::GetCurrentWindow()->Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		m_StateMachine->PushState(std::make_unique<PauseMenu>(m_Window, m_CameraController, m_StateMachine));
	}

	void Level::Resume()
	{
		Novaura::InputHandler::SetCurrentController(m_InputController);
		glfwSetInputMode(Novaura::InputHandler::GetCurrentWindow()->Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	void Level::DeathAnimation()
	{
	}
}
