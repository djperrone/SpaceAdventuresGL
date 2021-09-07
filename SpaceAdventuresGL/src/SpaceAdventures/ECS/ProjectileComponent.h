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

	public:
		inline int GetMagazineSize() const { return m_MagazineSize; }
		inline int GetBulletsUsed() const { return m_UseCount; }

	private:

		std::vector<std::shared_ptr<Projectile>> m_ProjectileList;
		Novaura::Rectangle* m_TransformComponent;
		MovementComponent* m_MovementComponent;
		Team m_Team;

		double currentTime = 0;
		double previousTime = 0;
		double ReloadStartTime = 0;
		double fireRate =0.25;

		int m_MagazineSize = 10;
		int m_UseCount = 0;

		double m_ReloadTime = 2.0;

		bool m_IsReloading = false;


	};
}