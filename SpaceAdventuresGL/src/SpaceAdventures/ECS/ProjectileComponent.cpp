#include "sapch.h"
#include "ProjectileComponent.h"

#include "SpaceAdventures/ECS/MovementComponent.h"


#include "Novaura/Primitives/Rectangle.h"
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
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
			float currentTime = glfwGetTime() - ReloadStartTime;
			if (currentTime >= m_ReloadTime)
			{
				m_UseCount = 0;
				m_IsReloading = false;
			}
			else
			{
				m_UseCount = glm::mix(0.0f, (float)m_ReloadTime, currentTime);
			}
		}
	}

	void ProjectileComponent::FireGun()
	{
		/*glm::vec2 spawnLoc = { m_TransformComponent->GetPosition() };

		m_ProjectileList.emplace_back(std::move(std::make_shared<Projectile>(spawnLoc,
			m_MovementComponent->GetVelocity(), m_Team, m_TransformComponent->GetRotation())));*/

		if (!m_IsReloading)
		{
			if (m_UseCount >= m_MagazineSize)
			{
				Reload();
				
				return;
				//return false;
			}

			currentTime = glfwGetTime();
			if (currentTime - previousTime >= fireRate)
			{
			
				glm::vec2 spawnLoc = { m_TransformComponent->GetPosition() };
				

				m_ProjectileList.emplace_back(std::move(std::make_shared<Projectile>(spawnLoc,
					m_MovementComponent->GetVelocity(), m_Team, m_TransformComponent->GetRotation())));

				previousTime = currentTime;

				m_UseCount++;
				if (m_UseCount >= m_MagazineSize)
				{
					Reload();

					return;
					//return false;
				}
			}
			//return true;
		}
		//return false;
	}
	void ProjectileComponent::ClearGun()
	{
		m_ProjectileList.clear();
	}
}