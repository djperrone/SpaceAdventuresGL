#pragma once
#include "Actor.h"
#include "SpaceAdventures/ECS/MovementComponent.h"
#include "SpaceAdventures/ECS/MovementComponent.h"
#include "SpaceAdventures/ECS/CombatComponent.h"



namespace SpaceAdventures {

	enum class Tag
	{
		None = 0,
		Asteroid,
		Ship,
		Player,
		Projectile
	};

	enum class Team
	{
		None = 0,
		Friend,
		Enemy
	};

	class Character : public Actor
	{
	public:
		Character() = default;
		Character(std::string_view textureFile, const glm::vec2& position, const glm::vec2& scale, float rotation, const::glm::vec2& velocity, float speed, float health, float damage);
		Character(std::string_view textureFile, const Novaura::Rectangle& rect, const MovementComponent& mc, const CombatComponent& cc);
		//Character(std::string_view textureFile, Novaura::Rectangle&& rect, MovementComponent&& mc, CombatComponent&& cc);

		virtual ~Character() = default;
		
		glm::vec2 GetVelocity() const;
		void SetVelocity(glm::vec2 velocity);		

		float GetSpeed() const;
		void SetSpeed(float speed);

		void UpdateLocation(float dt);

		float GetLeftBound() const;
		float GetRightBound()const;
		float GetUpperBound()const;
		float GetLowerBound()const;

		float GetHealth() const;
		float GetDamage() const;

		void TakeDamage(float damage);
		void Attack(Character* Character);
		bool IsAlive() const;

		Team GetTeam()const;
		Tag GetTag() const;

		inline float GetMaxHealth() { return m_CombatComponent->GetMaxHealth(); }

	protected:
		std::unique_ptr<MovementComponent> m_MovementComponent;
		std::unique_ptr<CombatComponent> m_CombatComponent;

		Team m_Team;
		Tag m_Tag = Tag::None;
		//ColliderComponent m_ColliderComponent;
	};
}