#include "sapch.h"
#include "StateMachine.h"
#include "State.h"

namespace Novaura {
 
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
    void StateMachine::ShutDown()
    {
        exit(0);
    }
}