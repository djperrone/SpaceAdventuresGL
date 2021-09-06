#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
#include "Novaura/Primitives/Rectangle.h"

class PauseMenu : public Novaura::State
{
public:
	PauseMenu() = default;
	PauseMenu(Novaura::Window & window);
	PauseMenu(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController);

	virtual void HandleInput() override;
	virtual void Update(float deltaTime)override;
	virtual void Draw(float deltaTime) override;

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Pause() override;
	virtual void Resume() override;
	
private:



};