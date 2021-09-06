#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"
#include "Novaura/Input/InputHandler.h"

#include "Novaura/Core/Window.h"

namespace SpaceAdventures {



	class TestState : public Novaura::State
	{
	public:
		TestState() = default;
		TestState(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> m_CameraController);
		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;

		

	private:	
		std::unique_ptr<Novaura::Rectangle> m_Rect;

	};
}