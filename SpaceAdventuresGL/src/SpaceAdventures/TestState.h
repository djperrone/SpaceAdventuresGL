#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"
namespace SpaceAdventures {



	class TestState : public Novaura::State
	{
	public:
		TestState() = default;
		TestState(Novaura::Window& window);
		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;

		Novaura::Window& GetWindow() { return m_Window; }
		const Novaura::Window& GetWindow() const { return m_Window; }

	private:
		Novaura::Window& m_Window;
		std::unique_ptr<Novaura::Rectangle> m_Rect;
		Novaura::CameraController m_CameraController;
	};
}