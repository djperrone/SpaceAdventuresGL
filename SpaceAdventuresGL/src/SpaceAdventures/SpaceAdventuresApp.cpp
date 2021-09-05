#include "sapch.h"
#include "SpaceAdventuresApp.h"
#include "TestState.h"


namespace SpaceAdventures {
	SpaceAdventuresApp::SpaceAdventuresApp()
	{
		m_StateMachine.PushState(std::make_unique<TestState>(GetWindow(),m_CameraController));
	}
}