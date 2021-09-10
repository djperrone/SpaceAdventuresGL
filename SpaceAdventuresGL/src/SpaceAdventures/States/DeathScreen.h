#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"
#include "UI/ToggleButton.h"


namespace SpaceAdventures {

	//class Button;

	class DeathScreen : public Novaura::State
	{
	public:
		DeathScreen();
	
		DeathScreen(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine);

		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;
		
	private:	
		std::vector<std::unique_ptr<UI::Button>> m_ButtonList;
		std::unique_ptr<Novaura::Rectangle> m_Title;
		

	};
}