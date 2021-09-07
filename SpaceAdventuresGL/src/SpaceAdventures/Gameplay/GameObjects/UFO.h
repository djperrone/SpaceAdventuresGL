#pragma once
#include "SpaceAdventures/Gameplay/GameObjects/SpaceShip.h"

namespace SpaceAdventures {

	class UFO : public Ship
	{
	public:
		UFO() = default;
		UFO(glm::vec2 pos);
		UFO(float x, float y);

		//virtual void FireGun() override;
		virtual void Update(float dt) override;

	private:
		time_t currentTime;
		time_t previousTime;
		double FIRE_RATE = 3;

	};
}