#pragma once
#include "SpaceAdventures/ECS/Component.h"

#include "SpaceAdventures/GamePlay/GameObjects/Projectile.h"

namespace SpaceAdventures {

	class Novaura::Rectangle;
	class Projectile;
	class MovementComponent;

	class ProjectileComponent : public Component
	{
	public:
		ProjectileComponent(Novaura::Rectangle* transform, MovementComponent* movement, Team team);
		void Reload();
		virtual void Update() override;
		void FireGun();
		void ClearGun();
		inline std::vector<std::shared_ptr<Projectile>>& GetProjectileList() { return m_ProjectileList; }
		
		inline bool IsReloading() const { return m_IsReloading; }

	private:

		std::vector<std::shared_ptr<Projectile>> m_ProjectileList;
		Novaura::Rectangle* m_TransformComponent;
		MovementComponent* m_MovementComponent;
		Team m_Team;

		uint32_t currentTime = 0;
		uint32_t previousTime = 0;
		uint32_t ReloadStartTime = 0;
		uint32_t fireRate = 250;

		int m_MagazineSize = 10;
		int m_UseCount = 0;

		uint32_t m_ReloadTime = 2500;

		bool m_IsReloading = false;


	};
}