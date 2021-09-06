#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"

namespace SpaceAdventures {


	class DeathScreen : public Novaura::State
	{
	public:
		DeathScreen() = default;
		DeathScreen(Novaura::Window& window);
		DeathScreen(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController);

		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;
		
	private:

		

	};
}