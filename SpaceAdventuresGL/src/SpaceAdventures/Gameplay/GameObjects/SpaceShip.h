#pragma once
#include "SpaceAdventures/Actors/Character.h"
#include "SpaceAdventures/ECS/ProjectileComponent.h"
#include "SpaceAdventures/GamePlay/GameObjects/Projectile.h"
#include <spdlog/spdlog.h>

namespace SpaceAdventures {

	class Ship : public Character
	{
	public:			

		virtual ~Ship() = default;
		virtual void FireGun() { /*spdlog::info("firing gun from ship class");	*/m_Gun->FireGun(); }
		inline bool IsReloading() { return m_Gun->IsReloading(); }
		virtual void Update(float dt) override {}

		inline std::vector<std::shared_ptr<Projectile>>& GetProjectileList()
		{
			return m_Gun->GetProjectileList();
		}	

	protected:

		std::unique_ptr<ProjectileComponent> m_Gun;	

	};
}