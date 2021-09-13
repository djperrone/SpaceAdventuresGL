#include "sapch.h"
#include "Projectile.h"
#include <spdlog/spdlog.h>

#include "Novaura/Novaura.h"
namespace SpaceAdventures {
	Projectile::Projectile()
	{
		
		//m_Rect = std::make_unique<Novaura::Rectangle>();
		m_MovementComponent = std::make_unique<MovementComponent>();
		m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);
		m_CombatComponent->SetMaxHealth(1);
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(0.15f, 0.15f), 0.0f);

		/*if (team == Team::Friend)
		{
			m_TextureFile = "Assets/Textures/Projectile_64.png";
		}
		else
		{
			m_TextureFile = "Assets/Textures/Projectile_64_enemy.png";
		}*/
		m_TextureFile = "Assets/Textures/Projectile_64_enemy.png";

		m_Tag = Tag::Projectile;
	}
	Projectile::Projectile(glm::vec2 position, glm::vec2 velocity, Team team, float angle)
	{
		m_Team = team;
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(position), glm::vec2(0.15f, 0.15f),angle);		
		m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle))), 1.0f);
		m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);			  
		m_CombatComponent->SetMaxHealth(1);

		if (team == Team::Friend)
		{			
			m_TextureFile = "Assets/Textures/Projectile_64.png";
		}
		else
		{
			m_TextureFile = "Assets/Textures/Projectile_64_enemy.png";
		}

		m_Tag = Tag::Projectile;					
	}

	void Projectile::Reset(const Projectile& other)
	{
		SetHealth(GetMaxHealth());
		SetTeam(other.GetTeam());
		SetPosition(other.GetRectangle().GetPosition());
		SetVelocity(other.GetVelocity());
		SetSpeed(other.GetSpeed());
		m_Rect->SetRotation(other.GetRectangle().GetRotation());
		m_IsCollidable = true;

		if (m_Team == Team::Friend)
		{
			m_TextureFile = "Assets/Textures/Projectile_64.png";
		}
		else
		{
			m_TextureFile = "Assets/Textures/Projectile_64_enemy.png";
		}
	}

	//void Projectile::Reset(const glm::vec3& position, glm::vec2 velocity, Team team, float angle)
	//{
	//	m_Team = team;
	//	m_Rect->SetPosition(position);
	//	SetVelocity(velocity);
	//	SetTeam(team);
	//	m_Rect->SetRotation(angle);
	//	m_MovementComponent

	//	//m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(position), glm::vec2(0.15f, 0.15f), angle);
	//	m_MovementComponent = std::make_unique<MovementComponent>(glm::vec2(glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle))), 1.0f);
	//	m_CombatComponent = std::make_unique<CombatComponent>(1.0f, 1.0f);
	//	m_CombatComponent->SetMaxHealth(1);

	//	if (team == Team::Friend)
	//	{
	//		m_TextureFile = "Assets/Textures/Projectile_64.png";
	//	}
	//	else
	//	{
	//		m_TextureFile = "Assets/Textures/Projectile_64_enemy.png";
	//	}

	//	m_Tag = Tag::Projectile;
	//}

	void Projectile::Update(float dt)
	{	
		m_Rect->GetPosition().y += m_MovementComponent->GetVelocity().y * dt * m_MovementComponent->GetSpeed();
		m_Rect->GetPosition().x += m_MovementComponent->GetVelocity().x * dt * m_MovementComponent->GetSpeed();		
	}
}