#include "sapch.h"
#include "UFO.h"

namespace SpaceAdventures {

	UFO::UFO(glm::vec2 pos)
	{
		m_Gun = std::make_unique<ProjectileComponent>(m_Rect.get(), m_MovementComponent.get(), m_Team);
		//m_Rect = std::make_unique<Novaura::Rectangle>(pos, 1.0);

	}

	UFO::UFO(float x, float y)
	{
		//m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(x,y));		

		m_Tag = Tag::Ship;
		m_Team = Team::Enemy;

		m_TextureFile = "Assets/Textures/UFO.png";

		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(x, y), glm::vec2(0.25f, 0.25f));
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(0.0f, 0.0f), 0.5f);
		m_CombatComponent = std::make_unique<CombatComponent>(3.0f, 3.0f);
		m_Gun = std::make_unique<ProjectileComponent>(m_Rect.get(), m_MovementComponent.get(), m_Team);
		m_Rect->SetPosition(glm::vec3(x,y,-0.1f));


	}

	void UFO::Update(float dt)
	{
		//UpdateLocation(dt);

		time(&currentTime);
		if (currentTime - previousTime >= 2)
		{
			FireGun();
			previousTime = currentTime;
		}
	}

}