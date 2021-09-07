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
		
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(1.0f, 1.0f), 0.5f);
		m_CombatComponent = std::make_unique<CombatComponent>(3.0f, 3.0f);
		m_Gun = std::make_unique<ProjectileComponent>(m_Rect.get(), m_MovementComponent.get(), m_Team);


		m_Tag = Tag::Player;

		/*InitComponents(350, 400, 32, 32, 3.5f, 90.0f, 4.0f, 0.0f, 0.0f, 5.0f, 1.0f);
		InitGun();
		InitController();*/
		m_PreviousPosition = m_Rect->GetPosition();

		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_W, &Player::MoveUp, this);
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_S, &Player::MoveDown, this);
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_A, &Player::MoveLeft, this);
		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_D, &Player::MoveRight, this);

		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_MOUSE_BUTTON_LEFT, &Player::FireGun, this);
		Novaura::InputHandler::GetCurrentController().BindActionInputEvent(GLFW_PRESS, GLFW_KEY_R, &Player::Reload, this);

		Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_T, []() {spdlog::info("test axis event T"); });
		//Novaura::InputHandler::GetCurrentController().BindAxisInputEvent(GLFW_KEY_S, &Player::MoveDown, this);


	}


	void Player::FireGun()
	{
		m_Gun->FireGun();
	}

	void Player::MoveUp()
	{
		//SetYVelocity(-1);
		//SetYPosition(GetYPosition() + -1 * GetSpeed());

		m_Rect->GetPosition().y += m_MovementComponent->GetVelocity().y * m_DeltaTime * m_MovementComponent->GetSpeed();

	}

	void Player::MoveDown()
	{
		m_Rect->GetPosition().y -= m_MovementComponent->GetVelocity().y * m_DeltaTime * m_MovementComponent->GetSpeed();

		//SetYVelocity(1);
		//SetYPosition(GetYPosition() + 1 * GetSpeed());
	}

	void Player::MoveLeft()
	{
		//SetXVelocity(-1);
		//SetXPosition(GetXPosition() + -1 * GetSpeed());
		m_Rect->GetPosition().x -= m_MovementComponent->GetVelocity().x * m_DeltaTime * m_MovementComponent->GetSpeed();

	}

	void Player::MoveRight()
	{
		//SetXVelocity(1);
		/*m_Rect->GetPosition().y += m_MovementComponent->GetVelocity().y * dt * m_MovementComponent->GetSpeed();
		m_Rect->GetPosition().x += m_MovementComponent->GetVelocity().x * dt * m_MovementComponent->GetSpeed();
		SetXPosition(GetXPosition() + 1 * GetSpeed());*/
		m_Rect->GetPosition().x += m_MovementComponent->GetVelocity().x * m_DeltaTime * m_MovementComponent->GetSpeed();
	}



	void Player::Update(float dt)
	{
		m_DeltaTime = dt;
		m_Gun->Update();

		Novaura::MousePosition pos = Novaura::InputHandler::GetMouseDeviceCoordinates();

		float dx = (pos.x - m_Rect->GetPosition().x);
		float dy = (pos.y - m_Rect->GetPosition().y);

		float angle;
		angle = atan2(dy, dx) * (180 / 3.146f);

		m_Rect->SetRotation(angle);

		//std::cout << "paused: " << Paused << std::endl;
		//float dx = (m_MouseCursor->GetXPosition() - GetXPosition());
		//float dy = (m_MouseCursor->GetYPosition() - GetYPosition());

		///*float dx = (m_MouseCursor->GetXPosition() + (m_MouseCursor->GetWidth() * m_MouseCursor->GetScale()) / 2 - GetXPosition() + (GetWidth() * GetScale() / 2));
		//float dy = (m_MouseCursor->GetYPosition() + (m_MouseCursor->GetHeight() * m_MouseCursor->GetScale()) / 2 - GetYPosition() + (GetHeight() * GetScale() / 2));*/
		//float angle;
		//angle = atan2(dy, dx) * (180 / 3.146f);

		////angle >= 0 ? angle : angle += 360;
		//SetAngle(angle);

		//glm::vec2 oldPos = m_TransformComponent->GetPositionVec();
		//UpdateLocation();
		//glm::vec2 currentPos = m_TransformComponent->GetPositionVec();

		//if (currentPos.x < -15 || currentPos.x > dimensions.WIDTH + 15 - m_TransformComponent->GetWidth() * m_TransformComponent->GetScale() ||
		//	currentPos.y < -15 || currentPos.y > dimensions.HEIGHT + 15 - m_TransformComponent->GetHeight() * m_TransformComponent->GetScale())
		//{
		//	m_TransformComponent->SetXPosition(m_PreviousPosition.x);
		//	m_TransformComponent->SetYPosition(m_PreviousPosition.y);
		//}

		///*else if (currentPos.x > dimensions.WIDTH +15 - m_TransformComponent->GetWidth() * m_TransformComponent->GetScale())
		//{
		//	m_TransformComponent->SetXPosition(m_PreviousPosition.x);
		//}*/

		///*else if (currentPos.y < -15)
		//{
		//	m_TransformComponent->SetYPosition(m_PreviousPosition.y);
		//}
		//else if (currentPos.y > dimensions.HEIGHT + 15 - m_TransformComponent->GetHeight() * m_TransformComponent->GetScale())
		//{
		//	m_TransformComponent->SetYPosition(m_PreviousPosition.y);
		//}*/
		//else
		//{
		//	m_PreviousPosition = currentPos;

		//}

		//m_TextureComponent->Update();
		//m_Gun->Update();
	}

	void Player::Reload()
	{
		
		m_Gun->Reload();
	
	}



}