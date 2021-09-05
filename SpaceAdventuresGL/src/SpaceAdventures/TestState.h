#pragma once
#include "Novaura/StateMachine/State.h"

class TestState : public Novaura::State
{
public:
	virtual void HandleInput() override;
	virtual void Update()override;
	virtual void Draw(float deltaTime) override;

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Pause() override;
	virtual void Resume() override;
};