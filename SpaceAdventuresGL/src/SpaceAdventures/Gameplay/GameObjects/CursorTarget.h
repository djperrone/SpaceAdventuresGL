#pragma once
#include "SpaceAdventures/Actors/Actor.h"
#include "SpaceAdventures/GamePlay/GameObjects/SpaceShip.h"
#include "SpaceAdventures/Gameplay/Managers/GameObjectData.h"

namespace SpaceAdventures {

	class CursorTarget : public Actor
	{
	public:
		CursorTarget();
		virtual void Update(float dt) override;
		void CheckForCollision(const std::vector<std::shared_ptr<Ship>>&);
	private:
		bool m_IsHovered = false;
	};
}