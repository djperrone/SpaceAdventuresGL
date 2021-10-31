#include "sapch.h"
#include "SpaceAdventuresApp.h"
#include "TestStates/TestState.h"
#include "TestStates/BatchTest.h"
#include "TestStates/StencilTest.h"
#include "TestStates/TextTest.h"
#include "States/MainMenu.h"
#include "TestStates/ButtonTest.h"
#include "TestStates/CircleTest.h"


namespace SpaceAdventures {
	SpaceAdventuresApp::SpaceAdventuresApp()
	{
		//m_StateMachine.PushState(std::make_unique<TestState>(GetWindow(),m_CameraController));
	}
	SpaceAdventuresApp::SpaceAdventuresApp(std::string_view title, float width, float height)
		:Application(title, width, height)
	{
		// test states
		//m_StateMachine.PushState(std::make_unique<TestState>(GetWindow(), m_CameraController));
		
		//m_StateMachine->PushState(std::make_unique<TestState>(GetWindow(), m_CameraController, m_StateMachine));
		//m_StateMachine->PushState(std::make_unique<TextTest>(GetWindow(), m_CameraController));
		//m_StateMachine->PushState(std::make_unique<BatchTest>(GetWindow(), m_CameraController, m_StateMachine));
		//m_StateMachine->PushState(std::make_unique<StencilTest>(GetWindow(), m_CameraController, m_StateMachine));
		//m_StateMachine->PushState(std::make_unique<ButtonTest>(GetWindow(), m_CameraController));

		//m_StateMachine->PushState(std::make_unique<CircleTest>(GetWindow(), m_CameraController, m_StateMachine));
		// Actual Gameplay
		m_StateMachine->PushState(std::make_unique<MainMenu>(GetWindow(), m_CameraController, m_StateMachine));
	}
}