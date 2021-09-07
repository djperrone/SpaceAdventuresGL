#include "sapch.h"
#include "ProjectileComponent.h"

#include "SpaceAdventures/ECS/MovementComponent.h"


#include "Novaura/Primitives/Rectangle.h"
#include <GLFW/glfw3.h>

namespace SpaceAdventures {
	ProjectileComponent::ProjectileComponent(Novaura::Rectangle* transform, MovementComponent* movement, Team team)
		: m_TransformComponent(transform), m_MovementComponent(movement), m_Team(team)
	{
		previousTime = glfwGetTime();
		previousTime -= fireRate;
		m_IsReloading = false;
	}

	void ProjectileComponent::Reload()
	{
		if (!m_IsReloading)
		{
			ReloadStartTime = glfwGetTime();
			m_IsReloading = true;
		}
	}

	void ProjectileComponent::Update()
	{
		if (m_IsReloading)
		{
			if (glfwGetTime() - ReloadStartTime > m_ReloadTime)
			{
				m_UseCount = 0;
				m_IsReloading = false;
			}
		}
	}

	bool ProjectileComponent::FireGun()
	{

		if (!m_IsReloading)
		{
			if (m_UseCount >= m_MagazineSize)
			{
				Reload();
				return false;
			}


			currentTime = glfwGetTime();
			if (currentTime - previousTime >= fireRate)
			{
				glm::vec2 spawnLoc = { m_TransformComponent->GetPosition() };
				

				m_ProjectileList.emplace_back(std::move(std::make_shared<Projectile>(spawnLoc,
					m_MovementComponent->GetVelocity(), m_Team, m_TransformComponent->GetRotation())));

				previousTime = currentTime;

				m_UseCount++;
			}
			return true;
		}
		return false;
	}
	void ProjectileComponent::ClearGun()
	{
		m_ProjectileList.clear();
	}
}