#include "sapch.h"
#include "Character.h"

namespace SpaceAdventures {
	Character::Character(std::string_view textureFile, const glm::vec2& position, const glm::vec2& scale, float rotation, const::glm::vec2& velocity, float speed, float health, float damage)
	{
		m_TextureFile = textureFile;
		m_Rect = std::make_unique<Novaura::Rectangle>(position, scale);
		m_MovementComponent = std::make_unique<MovementComponent>(velocity, speed);
		m_CombatComponent = std::make_unique<CombatComponent>(health, damage);
	}
	Character::Character(std::string_view textureFile, const Novaura::Rectangle& rect, const MovementComponent& mc, const CombatComponent& cc)
	{
	}

	glm::vec2 Character::GetVelocity() const { return m_MovementComponent->GetVelocity(); }
	void Character::SetVelocity(glm::vec2 velocity) { m_MovementComponent->SetVelocity(velocity); }
	
	float Character::GetSpeed() const { return m_MovementComponent->GetSpeed(); }
	void Character::SetSpeed(float speed) { m_MovementComponent->SetSpeed(speed); }

	void Character::UpdateLocation(float dt)
	{
		glm::vec3 pos;
		pos.x = m_Rect->GetPosition().x * m_MovementComponent->GetVelocity().x * m_MovementComponent->GetSpeed() * dt;
		pos.y = m_Rect->GetPosition().y * m_MovementComponent->GetVelocity().y * m_MovementComponent->GetSpeed() * dt;

		m_Rect->SetPosition(pos);
	}

	
	
	
	float Character::GetHealth() const { return m_CombatComponent->GetHealth(); }
	float Character::GetDamage() const { return m_CombatComponent->GetDamage(); }
	void Character::TakeDamage(float damage) { m_CombatComponent->TakeDamage(damage); }
	void Character::Attack(Character* Character) { m_CombatComponent->Attack(Character); }
	bool Character::IsAlive() const { return GetHealth() > 0; }
	Team Character::GetTeam()const { return m_Team; }
	Tag Character::GetTag() const { return m_Tag; }
}