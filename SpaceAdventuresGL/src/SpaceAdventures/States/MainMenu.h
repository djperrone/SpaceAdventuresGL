#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"

#include "SpaceAdventures/Actors/Button.h"


namespace SpaceAdventures {

	class Button;

	class MainMenu : public Novaura::State
	{
	public:
		MainMenu() = default;
		MainMenu(Novaura::Window & window);
		MainMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController);


		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;
		
	private:			

		/*std::vector<std::unique_ptr<StaticSprite>> m_SpriteList;
		std::vector<std::unique_ptr<Button>> m_ButtonList;*/
		std::unique_ptr<Button> m_Button;

	};
}
