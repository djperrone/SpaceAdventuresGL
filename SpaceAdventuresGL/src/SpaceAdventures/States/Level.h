#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"

#include "SpaceAdventures/Gameplay/Managers/ObjectManager.h"
namespace SpaceAdventures {

	class Level : public Novaura::State
	{
	public:
		Level() = default;
		Level(Novaura::Window & window);
		Level(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine);

		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;

	
	private:
		double m_CurrentTime = 0.0;
		double m_PreviousTime = 0.0;
		int bulletCounter = 0;
		double m_DisplayTime = 0.25;
		std::unique_ptr<ObjectManager> m_ObjectManager;

	};
}
