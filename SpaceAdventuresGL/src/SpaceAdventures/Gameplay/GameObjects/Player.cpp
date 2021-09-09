#include "sapch.h"
#include "Player.h"
#include "Novaura/Novaura.h"

namespace SpaceAdventures {


	Player::Player()
	{
		//m_MouseCursor = mouseCursor;
		std::cout << "player!\n";

		m_Team = Team::Friend;
		m_TextureFile = "Assets/Textures/Spaceship.png";
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.25f));
		m_Rect->SetRotation(90.0f);
		
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(1.0f, 1.0f), 1.0f);
		m_CombatComponent = std::make_unique<CombatComponent>(3.0f, 3.0f);
		m_Gun = std::make_unique<ProjectileComponent>(m_Rect.get(), m_MovementComponent.get(), m_Team);


		m_Tag = Tag::Player;
		m_Team = Team::Friend;

		m_PreviousPosition = m_Rect->GetPosition();

		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_W, &Player::MoveUp, this);
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_S, &Player::MoveDown, this);
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_A, &Player::MoveLeft, this);
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_D, &Player::MoveRight, this);

		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, &Player::FireGun, this);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_KEY_R, &Player::Reload, this);

		//Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });
	}

	void Player::FireGun()
	{
		m_Gun->FireGun();
	}

	void Player::MoveUp()
	{
		m_Rect->GetPosition().y += m_MovementComponent->GetVelocity().y * m_DeltaTime * m_MovementComponent->GetSpeed();
	}

	void Player::MoveDown()
	{
		m_Rect->GetPosition().y -= m_MovementComponent->GetVelocity().y * m_DeltaTime * m_MovementComponent->GetSpeed();		
	}

	void Player::MoveLeft()
	{		
		m_Rect->GetPosition().x -= m_MovementComponent->GetVelocity().x * m_DeltaTime * m_MovementComponent->GetSpeed();
	}

	void Player::MoveRight()
	{		
		m_Rect->GetPosition().x += m_MovementComponent->GetVelocity().x * m_DeltaTime * m_MovementComponent->GetSpeed();
	}

	void Player::Update(float dt)
	{
		m_DeltaTime = dt;
		m_Gun->Update();
		//spdlog::info("playe health: {0}", m_CombatComponent->GetHealth());
		Novaura::MousePosition pos = Novaura::InputHandler::GetMouseDeviceCoordinates();

		float dx = (pos.x - m_Rect->GetPosition().x);
		float dy = (pos.y - m_Rect->GetPosition().y);

		float angle;
		angle = atan2(dy, dx) * (180 / 3.146f);

		m_Rect->SetRotation(angle);
	}

	void Player::Reload()
	{		
		m_Gun->Reload();	
	}



}