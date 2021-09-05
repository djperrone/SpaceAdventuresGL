#pragma once
#include "State.h"
namespace Novaura {

	class StateMachine
	{
	public:
		StateMachine();

		void PushState(std::unique_ptr<State> state);
		void ReplaceCurrentState(std::unique_ptr<State> state);
		void PopState();

		inline State& GetCurrentState() { return *m_States.top(); }
		inline const State& GetCurrentState() const { return *m_States.top(); }

	private:
		std::stack<std::unique_ptr<State>> m_States;

	};

}