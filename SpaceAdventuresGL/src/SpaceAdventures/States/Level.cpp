#include "sapch.h"
#include "Level.h"

namespace SpaceAdventures {


	Level::Level(Novaura::Window& window)		
	{
		
	}

	Level::Level(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
	{
		m_Window = window;
		m_CameraController = cameraController;

		OnEnter();
	}

	void Level::HandleInput()
	{
	}

	void Level::Update(float deltaTime)
	{
	}

	void Level::Draw(float deltaTime)
	{
	}

	void Level::OnEnter()
	{
	}

	void Level::OnExit()
	{
	}

	void Level::Pause()
	{
	}

	void Level::Resume()
	{
	}
}
