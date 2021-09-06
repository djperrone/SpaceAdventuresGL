#include "sapch.h"
#include "CombatComponent.h"
#include "SpaceAdventures/Actors/Character.h"

namespace SpaceAdventures {

	void CombatComponent::Attack(Character* Character)
	{
		Character->TakeDamage(GetDamage());
	}
}