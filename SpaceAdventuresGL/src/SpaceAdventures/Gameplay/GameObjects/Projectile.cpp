#include "sapch.h"
#include "Projectile.h"
#include <spdlog/spdlog.h>

#include "Novaura/Novaura.h"
namespace SpaceAdventures {

	Projectile::Projectile(glm::vec2 position, glm::vec2 velocity, Team team, float angle)
	{
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(position), glm::vec2(0.15f, 0.15f),angle);
		//m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2((cos(angle) * 3.14159 / 180.0f), (sin(angle) * 3.14159 / 180.0f)), 10.0f);
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle))), 1.0f);
		m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);			  
		//m_Rect->SetPosition({ position, 0.1f });
		if (team == Team::Friend)
		{
			//m_MovementComponent->GetVelocity().y = -1.0f; 
			//m_MovementComponent->SetVelocity(glm::vec2(m_MovementComponent->GetVelocity().x, m_MovementComponent->GetVelocity().y * -1.0f ));


			//m_MovementComponent->SetVelocity(glm::vec2(1.0f, 1.0f));
			m_TextureFile = "Assets/Textures/Projectile_64.png";
		

		}
		else
		{
			m_TextureFile = "Assets/Textures/Projectile_64_enemy.png";
			//m_MovementComponent->SetVelocity(glm::vec2(-1.0f, -1.0f));
			//m_MovementComponent->SetVelocity(glm::vec2(0.0f, m_MovementComponent->GetVelocity().y * -1.0f));



		}
		//m_Rect->SetPosition(glm::vec3(position, -0.3f));

		//float xRad = glm::degrees(cos(180.0f));
		//float yRad = glm::degrees(glm::sin(180.0f));
		//float xRad = glm::degrees(glm::cos(180.0f));

		/*float yRad = m_Rect->GetRotation() / 180.0f ;
		float xRad = m_Rect->GetRotation() / 180.0f;*/
		//float yRad = sin(0.0f);

		//float yRad = glm::sin(glm::radians(angle));
		//float xRad = glm::cos(glm::radians(angle));
		////spdlog::info("x: {0},  y {1} ", xRad, yRad);
		
		//m_MovementComponent->SetVelocity(glm::vec2(xRad, yRad));
	
		m_Tag = Tag::Projectile;	
		
		//m_Rect->SetColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
		
	}

	void Projectile::Update(float dt)
	{
		/*float yRad = sin((m_Rect->GetRotation()));
		float xRad = cos((m_Rect->GetRotation()));*/

		/*float yRad = sin(glm::radians(m_Rect->GetRotation()));
		float xRad = cos(glm::radians(m_Rect->GetRotation())); */
		//m_MovementComponent->SetVelocity(glm::vec2(xRad, yRad));
		/*spdlog::info("x: {0},  y {1} ", m_MovementComponent->GetVelocity().x, m_MovementComponent->GetVelocity().y);
		spdlog::info("cos 180 {0}",cos(180));*/

		/*Novaura::MousePosition pos = Novaura::InputHandler::GetMouseDeviceCoordinates();

		float dx = (pos.x - m_Rect->GetPosition().x);
		float dy = (pos.y - m_Rect->GetPosition().y);

		float angle;
		angle = atan2(dy, dx) * (180 / 3.146f);

		float yRad = glm::sin(glm::radians(angle));
		float xRad = glm::cos(glm::radians(angle));*/
		//spdlog::info("x: {0},  y {1} ", xRad, yRad);

		//m_MovementComponent->SetVelocity(glm::vec2(xRad, yRad));




		m_Rect->GetPosition().y += m_MovementComponent->GetVelocity().y * dt * m_MovementComponent->GetSpeed();
		m_Rect->GetPosition().x += m_MovementComponent->GetVelocity().x * dt * m_MovementComponent->GetSpeed();

		//UpdateLocation(dt);
		//m_TextureComponent->Update();
	}


}