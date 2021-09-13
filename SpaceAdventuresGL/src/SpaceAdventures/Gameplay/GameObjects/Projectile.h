#pragma once
#include "SpaceAdventures/Actors/Character.h"

namespace SpaceAdventures {

	class Projectile : public Character
	{
	public:

		Projectile();
		Projectile(glm::vec2 position, glm::vec2 velocity, Team team, float angle);
		void Reset(const Projectile& other);


		virtual void Update(float dt) override;
	};
}