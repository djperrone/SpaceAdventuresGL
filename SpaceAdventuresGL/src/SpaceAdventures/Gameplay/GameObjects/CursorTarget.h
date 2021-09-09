#pragma once
#include "SpaceAdventures/Actors/Actor.h"
#include "SpaceAdventures/GamePlay/GameObjects/SpaceShip.h"

namespace SpaceAdventures {

	class CursorTarget : public Actor
	{
	public:
		CursorTarget();
		virtual void Update(float dt) override;
		void CheckForCollision(const std::list<std::shared_ptr<Ship>>& shipList);
	private:
		bool m_IsHovered = false;
	};
}