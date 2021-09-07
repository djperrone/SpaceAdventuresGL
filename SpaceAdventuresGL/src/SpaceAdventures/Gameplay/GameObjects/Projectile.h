#pragma once
#include "SpaceAdventures/Actors/Character.h"

namespace SpaceAdventures {

	class Projectile : public Character
	{
	public:

		Projectile() = default;

		Projectile(glm::vec2 position, glm::vec2 velocity, Team team, float angle);


		virtual void Update(float dt) override;
	};
}