#pragma once
#pragma once
#include "Component.h"

namespace SpaceAdventures {

	class Character;

	class CombatComponent : public Component
	{
	public:
		CombatComponent()
			:m_Health(1), m_Damage(0) {}

		CombatComponent(float health, float damage)
			: m_Health(health), m_Damage(damage) {}

		inline void TakeDamage(float damage)
		{
			m_Health -= damage;
		}
		COMPONENT_CLASS_TYPE(CombatComponent)

		void Attack(Character* Character);

		inline float GetHealth() const { return m_Health; }
		inline float GetDamage() const { return m_Damage; }
		inline void SetHealth(float health) { m_Health = health; }
		inline void SetDamage(float damage) { m_Damage = damage; }

	private:
		float m_Health, m_Damage;
	};
}
