#include "sapch.h"
#include "TestState.h"

#include <glm/glm.hpp>
#include "Novaura/Renderer/Renderer.h"
#include <spdlog/spdlog.h>

namespace SpaceAdventures {
	//TestState::TestState()
	//	: m_CameraController(GetWindow().Width, GetWindow().Height)
	//{
	//}
	TestState::TestState(Novaura::Window& window)
		: m_Window(window), m_CameraController(GetWindow().Width, GetWindow().Height)
	{
		OnEnter();
	}
	void TestState::HandleInput()
	{
	}

	void TestState::Update(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController.GetCamera());
		spdlog::info("application update test");
		Draw(deltaTime);

	}

	void TestState::Draw(float deltaTime)
	{
		Novaura::Renderer::SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		Novaura::Renderer::Clear();
		Novaura::Renderer::BeginScene(m_CameraController.GetCamera());
		Novaura::Renderer::DrawRotatedRectangle(*m_Rect);		

	}

	void TestState::OnEnter()
	{
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f), glm::vec2(0.4f, 0.4f));

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
