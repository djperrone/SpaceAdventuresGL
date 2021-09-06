#include "sapch.h"
#include "MainMenu.h"
#include "SpaceAdventures/Actors/Button.h"
#include "Novaura/Renderer/Renderer.h"

namespace SpaceAdventures {

	MainMenu::MainMenu(Novaura::Window& window)		
	{
		
	}

	MainMenu::MainMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
	{
		m_Window = window;
		m_CameraController = cameraController;
		//m_InputController

		OnEnter();
	}

	void MainMenu::HandleInput()
	{
	}

	void MainMenu::Update(float deltaTime)
	{
		Draw(deltaTime);
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
		Novaura::Renderer::DrawRotatedRectangle(m_Button->GetRectangle(), m_Button->GetTextureFile());
	}

	void MainMenu::Draw(float deltaTime)
	{
	}

	void MainMenu::OnEnter()
	{
		
		m_Button = std::make_unique<Button>("Assets/Textures/WoodenBox.png", ButtonType::Play, glm::vec2(0.0f,0.0f),glm::vec2(1.0f,1.0f));
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
