#pragma once

#include "SpaceAdventures/Gameplay/GameObjects/Projectile.h"
#include "SpaceAdventures/Gameplay/GameObjects/SpaceShip.h"

namespace SpaceAdventures {

	class ProjectileManager
	{
	public:
		ProjectileManager() = default;
		~ProjectileManager() { std::cout << "destroyed porjctile manager\n"; };

		static const uint32_t MAX_SHIPS = 32;


		inline std::vector<std::shared_ptr<Projectile>>& GetProjectileList()
		{
			return m_ProjectileList;
		}	

		inline const std::vector<std::shared_ptr<Projectile>>& GetProjectileList() const
		{
			return m_ProjectileList;
		}

		inline void ClearProjectileList()
		{
			m_ProjectileList.clear();
		}

		void LoadAllProjectiles(std::vector<std::shared_ptr<Ship>>& shipList);


	private:
		std::vector<std::shared_ptr<Projectile>> m_ProjectileList;	

	};
}