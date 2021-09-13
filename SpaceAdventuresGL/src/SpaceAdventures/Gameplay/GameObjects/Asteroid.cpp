#include "sapch.h"
#include "Asteroid.h"
#include <spdlog/spdlog.h>

namespace SpaceAdventures {

	Asteroid::Asteroid()		
	{
		m_Tag = Tag::Asteroid;
		m_Team = Team::Enemy;

		m_TextureFile = "Assets/Textures/Asteroid1.png";

		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0, 0), glm::vec2(0.25f, 0.25f));
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(0.0f, 1.0f), 0.5f);
		m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);		

		m_CombatComponent->SetMaxHealth(1);		
	}

	Asteroid::Asteroid(float x, float y)
	{		
		m_Tag = Tag::Asteroid;
		m_Team = Team::Enemy;

		m_TextureFile = "Assets/Textures/Asteroid1.png";

		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(x,y), glm::vec2(0.25f,0.25f));
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(0.0f,1.0f), 0.5f);
		m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);
		//m_Rect->SetPosition(glm::vec3(x, y, -0.2f));

		m_CombatComponent->SetMaxHealth(1);
		spdlog::error("Asteroid const");
	}

	void Asteroid::Update(float dt)
	{
		m_Rect->GetPosition().y -= m_MovementComponent->GetVelocity().y * dt * m_MovementComponent->GetSpeed();
		m_Rect->GetPosition().x += m_MovementComponent->GetVelocity().x * dt * m_MovementComponent->GetSpeed();
	}

	Asteroid::~Asteroid() { /*std::cout<<"destroyed asteroid\n";*/ }


}