#include "sapch.h"
#include "CircleTest.h"

#include <glm/glm.hpp>
#include "Novaura/Renderer/Renderer.h"
#include "Novaura/Renderer/BatchRenderer.h"
#include <spdlog/spdlog.h>

#include "Novaura/Renderer/Texture.h"
#include "Novaura/Renderer/TextureLoader.h"
#include "Novaura/Renderer/TextLoader.h"
#include "Novaura/Input/InputHandler.h"

namespace SpaceAdventures {	

	CircleTest::CircleTest(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine)
	{
		m_Window = window;
		m_CameraController = cameraController;
		m_StateMachine = stateMachine;
		OnEnter();
	}

	void CircleTest::OnEnter()
	{	

		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, -0.0f), glm::vec2(0.75f,0.75f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f));
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });

	}


	void CircleTest::HandleInput()
	{
	}

	void CircleTest::Update(float deltaTime)
	{
		m_CameraController->Update(GetWindow(), deltaTime);		
		float aspectRatio = m_Window->Width / m_Window->Height;				
		m_Rect->SetPosition(glm::vec3(m_Rect->GetPosition().x + 0.001, m_Rect->GetPosition().y - 0.0007, m_Rect->GetPosition().z));
	}

	void CircleTest::Draw(float deltaTime)
	{
		Novaura::BatchRenderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Novaura::BatchRenderer::Clear();
		Novaura::BatchRenderer::BeginScene(m_CameraController->GetCamera());	
		Novaura::BatchRenderer::DrawCircle(*m_Rect);

		Novaura::BatchRenderer::EndScene();
	}

	

	void CircleTest::OnExit()
	{
	}

	void CircleTest::Pause()
	{
	}

	void CircleTest::Resume()
	{
	}
}
