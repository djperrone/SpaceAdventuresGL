#include "sapch.h"
#include "StateMachine.h"

namespace Novaura {

    StateMachine::StateMachine()
    {
    }

    void StateMachine::PushState(std::unique_ptr<State> state)
    {
        m_States.push(std::move(state));
    }

    void StateMachine::ReplaceCurrentState(std::unique_ptr<State> state)
    {
        m_States.pop();
        m_States.push(std::move(state));
    }

    void StateMachine::PopState()
    {
        m_States.pop();
    }
}