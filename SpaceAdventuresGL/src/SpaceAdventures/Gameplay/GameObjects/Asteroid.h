#pragma once
#include "SpaceAdventures/Actors/Character.h"

namespace SpaceAdventures {

	class Asteroid : public Character
	{
	public:
		Asteroid();
		Asteroid(float x, float y);

		virtual void Update(float dt) override;
		~Asteroid();

	private:

	};
}