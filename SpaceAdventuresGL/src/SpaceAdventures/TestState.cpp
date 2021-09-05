#include "sapch.h"
#include "TestState.h"

#include <glm/glm.hpp>
#include "Novaura/Renderer/Renderer.h"
#include <spdlog/spdlog.h>

#include "Novaura/Renderer/Texture.h"
#include "Novaura/Renderer/TextureLoader.h"
#include "Novaura/Input/InputHandler.h"

namespace SpaceAdventures {
	//TestState::TestState()
	//	: m_CameraController(GetWindow().Width, GetWindow().Height)
	//{
	//}
	//TestState::TestState(std::shared_ptr<Window> window)
	//	: m_Window(window), m_CameraController(GetWindow().Width, GetWindow().Height)
	//{
	//	OnEnter();
	//}
	TestState::TestState(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController)
	{
		m_Window = window;
		m_CameraController = cameraController;

		OnEnter();
	}
	void TestState::HandleInput()
	{
	}
	namespace test {
		float velocity = 0.01f;
	}
	void TestState::Update(float deltaTime)
	{
		m_CameraController->Update(GetWindow(), deltaTime);		
		float aspectRatio = m_Window->Width / m_Window->Height;
		
		m_Rect->m_Position.x += test::velocity;
		if (m_Rect->m_Position.x > aspectRatio)
		{
			test::velocity *= -1;
		}

		if (m_Rect->m_Position.x < -aspectRatio)
		{
			test::velocity *= -1;
		}


		Draw(deltaTime);		

	}

	void TestState::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController->GetCamera());
		Novaura::Renderer::DrawRotatedRectangle(*m_Rect);		

	}

	void TestState::OnEnter()
	{
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.4f, 0.4f));
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });
		Novaura::Texture tex = TextureLoader::LoadTexture("Assets/Textures/Spaceship.png");
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_1, [m_Rect = &m_Rect]()
			{
				Novaura::MousePosition mPos = Novaura::InputHandler::GetMousePosition();
			spdlog::info("mouse x {0}, mouse y {1}", mPos.x, mPos.y); 
			spdlog::info("ship x {0}, ship y {1}", m_Rect->get()->m_Position.x, m_Rect->get()->m_Position.y); });
		
	}

	void TestState::OnExit()
	{
	}

	void TestState::Pause()
	{
	}

	void TestState::Resume()
	{
	}
}
