#include "sapch.h"
#include "DeathScreen.h"
namespace SpaceAdventures {

	DeathScreen::DeathScreen(Novaura::Window& window)		
	{
		
	}

	DeathScreen::DeathScreen(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
	{
		m_Window = window;
		m_CameraController = cameraController;

		OnEnter();
	}

	void DeathScreen::HandleInput()
	{
	}

	void DeathScreen::Update(float deltaTime)
	{
	}

	void DeathScreen::Draw(float deltaTime)
	{
	}

	void DeathScreen::OnEnter()
	{
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