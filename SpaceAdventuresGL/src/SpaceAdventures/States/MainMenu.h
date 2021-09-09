#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"

#include "SpaceAdventures/Actors/Button.h"

namespace SpaceAdventures {

	class Rectangle;

	class MainMenu : public Novaura::State
	{
	public:
		MainMenu() = default;
		MainMenu(Novaura::Window & window);
		MainMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine);

		virtual void OnEnter() override;

		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;
		virtual void HandleInput() override;

		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;		
		
	private:			
		
		std::vector<std::unique_ptr<Button>> m_ButtonList;
		std::unique_ptr<Novaura::Rectangle> m_Title;

	};
}
