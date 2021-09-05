#pragma once

#include "Novaura/Input/InputController.h"

namespace Novaura {

	class State
	{
	public:
		State() = default;		

		virtual void HandleInput() = 0;
		virtual void Update() = 0;
		virtual void Draw(float deltaTime) = 0;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		InputController& GetInputController(){return *m_InputController;}
		const InputController& GetInputController() const { return *m_InputController; }

		void SetController(std::shared_ptr<InputController> inputController) { m_InputController = inputController; }

		bool IsOverLay() { return m_IsOverlay; }
		bool SetIsOverLay(bool isOverlay) { m_IsOverlay = isOverlay; }

	private:
		std::shared_ptr<InputController> m_InputController;
		bool m_IsOverlay;
	};
}