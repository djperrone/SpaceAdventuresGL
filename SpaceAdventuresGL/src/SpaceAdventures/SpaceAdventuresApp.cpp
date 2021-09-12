#include "sapch.h"
#include "SpaceAdventuresApp.h"
#include "States/TestState.h"
#include "States/BatchTest.h"
#include "States/MainMenu.h"


namespace SpaceAdventures {
	SpaceAdventuresApp::SpaceAdventuresApp()
	{
		//m_StateMachine.PushState(std::make_unique<TestState>(GetWindow(),m_CameraController));
	}
	SpaceAdventuresApp::SpaceAdventuresApp(std::string_view title, float width, float height)
		:Application(title, width, height)
	{
		//m_StateMachine.PushState(std::make_unique<TestState>(GetWindow(), m_CameraController));
		m_StateMachine->PushState(std::make_unique<MainMenu>(GetWindow(), m_CameraController, m_StateMachine));
		//m_StateMachine->PushState(std::make_unique<TestState>(GetWindow(), m_CameraController, m_StateMachine));
		//m_StateMachine->PushState(std::make_unique<BatchTest>(GetWindow(), m_CameraController, m_StateMachine));
	}
}