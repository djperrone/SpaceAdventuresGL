#include "sapch.h"
#include "Asteroid.h"

namespace SpaceAdventures {

	Asteroid::Asteroid()		
	{
	
	}

	Asteroid::Asteroid(float x, float y)
	{
		m_Team = Team::Enemy;
		//std::cout << "Asteroid!" << static_cast<std::size_t>(m_Team) << std::endl;

		
		/*if (m_Team == Team::Enemy)
		{
			InitComponents(x, y, 32, 32, 2.0f, 0.0f, 1.5f, 0.0f, 1.0f, 1.0f, 1.0f);

		}*/

		m_Tag = Tag::Asteroid;
		m_Team = Team::Enemy;

		m_TextureFile = "Assets/Textures/Asteroid1.png";

		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(x,y), glm::vec2(0.25f,0.25f));
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(0.0f,1.0f), 0.5f);
		m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);
	}

	void Asteroid::Update(float dt)
	{
		m_Rect->GetPosition().y -= m_MovementComponent->GetVelocity().y * dt * m_MovementComponent->GetSpeed();
	}

	Asteroid::~Asteroid() { /*std::cout<<"destroyed asteroid\n";*/ }


}