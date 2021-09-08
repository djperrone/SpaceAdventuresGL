#pragma once
#pragma once
#include "Component.h"

namespace SpaceAdventures {

	class Character;

	class CombatComponent : public Component
	{
	public:
		CombatComponent()
			:m_CurrentHealth(1), m_MaxHealth(1), m_Damage(0) {}

		CombatComponent(float health, float damage)
			: m_CurrentHealth(health), m_MaxHealth(health), m_Damage(damage) {}

		inline void TakeDamage(float damage)
		{
			m_CurrentHealth -= damage;
		}
		COMPONENT_CLASS_TYPE(CombatComponent)

		void Attack(Character* Character);

		inline float GetHealth() const { return m_CurrentHealth; }
		inline float GetDamage() const { return m_Damage; }
		inline void SetHealth(float health) { m_CurrentHealth = health; }
		inline void SetDamage(float damage) { m_Damage = damage; }

		inline float GetMaxHealth() const { return m_MaxHealth; }
		inline void SetMaxHealth(float maxHealth) { m_MaxHealth = maxHealth; }

	private:
		float m_CurrentHealth, m_MaxHealth, m_Damage;
	};
}
