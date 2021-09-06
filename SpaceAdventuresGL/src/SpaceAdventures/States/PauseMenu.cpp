#include "sapch.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(Novaura::Window& window)	
{
	
}

PauseMenu::PauseMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
{
	m_Window = window;
	m_CameraController = cameraController;

	OnEnter();
}

void PauseMenu::HandleInput()
{
}

void PauseMenu::Update(float deltaTime)
{
}

void PauseMenu::Draw(float deltaTime)
{
}

void PauseMenu::OnEnter()
{
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
