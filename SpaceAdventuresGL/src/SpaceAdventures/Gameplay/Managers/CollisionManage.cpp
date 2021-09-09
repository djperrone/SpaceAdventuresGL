#include "sapch.h"
#include "CollisionManager.h"
#include "SpaceAdventures/Actors/Character.h"
#include "SpaceAdventures/GamePlay/GameObjects/Asteroid.h"
#include "SpaceAdventures/GamePlay/GameObjects/SpaceShip.h"
#include "SpaceAdventures/GamePlay/GameObjects/Projectile.h"

namespace SpaceAdventures {

	CollisionManager::CollisionManager(std::list<std::shared_ptr<Ship>>* objList, std::list<std::unique_ptr<Asteroid>>* asteroidList, std::list<std::shared_ptr<Character>>* projectileList)
		: m_ShipList(objList), m_AsteroidList(asteroidList), m_ProjectileList(projectileList)
	{
		
	}

	CollisionManager::CollisionManager()
		: m_AsteroidList(nullptr), m_ShipList(nullptr)
	{
	}

	void CollisionManager::Tick()
	{

		for (auto it = std::begin(*m_ShipList); it != std::end(*m_ShipList); it++)
		{
			//std::cout << "col man objlist " << (m_ShipList->size()) << "\n";

			for (auto otherIt = std::begin(*m_ShipList); otherIt != std::end(*m_ShipList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}

			for (auto otherIt = std::begin(*m_AsteroidList); otherIt != std::end(*m_AsteroidList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}

			for (auto otherIt = std::begin(*m_ProjectileList); otherIt != std::end(*m_ProjectileList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
				//	std::cout << "collision!\n";
				}
			}

		}

		for (auto it = std::begin(*m_AsteroidList); it != std::end(*m_AsteroidList); it++)
		{
			//std::cout << "Asteroidsadasdasdasd\n";
			for (auto otherIt = std::begin(*m_AsteroidList); otherIt != std::end(*m_AsteroidList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}

			for (auto otherIt = std::begin(*m_ShipList); otherIt != std::end(*m_ShipList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}
			for (auto otherIt = std::begin(*m_ProjectileList); otherIt != std::end(*m_ProjectileList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}

		}

		for (auto it = std::begin(*m_ProjectileList); it != std::end(*m_ProjectileList); it++)
		{
			//std::cout << "Asteroidsadasdasdasd\n";
			for (auto otherIt = std::begin(*m_AsteroidList); otherIt != std::end(*m_AsteroidList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}

			for (auto otherIt = std::begin(*m_ShipList); otherIt != std::end(*m_ShipList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}
			for (auto otherIt = std::begin(*m_ProjectileList); otherIt != std::end(*m_ProjectileList); otherIt++)
			{
				if (IsColliding(it->get(), otherIt->get()) && !IsOnSameTeam(it->get(), otherIt->get()))
				{
					HandleCollisionEvent(it->get(), otherIt->get());
					//std::cout << "collision!\n";
				}
			}

		}

		/*for (int i = 0; i < m_ShipList.size(); i++)
		{

		}*/


	}

	void CollisionManager::HandleCollisionEvent(Character* current, Character* other)
	{
		//std::cout << "collission detected!\n";
		current->Attack(other);
		//other->Attack(current);
	}

	bool CollisionManager::IsOnSameTeam(Character* current, Character* other)
	{
		//std::cout << "current team: " << static_cast<std::size_t>(current->GetTeam()) << ", other team: " << static_cast<std::size_t>(other->GetTeam()) << std::endl;
		return current->GetTeam() == other->GetTeam();
	}


	bool CollisionManager::IsColliding(Character* current, Character* other)
	{
		/*if (current->GetRightBound() >= other->GetLeftBound() &&
			other->GetRightBound() >= current->GetLeftBound() &&
			current->GetUpperBound() >= other->GetLowerBound() &&
			other->GetUpperBound() >= current->GetLowerBound())
		{
			return true;
		}

		return false;*/

		Bounds boundsA = current->GetBounds();
		Bounds boundsB = other->GetBounds();

		if (boundsA.BottomRight.x >= boundsB.BottomLeft.x &&
			boundsB.BottomRight.x >= boundsA.BottomLeft.x &&
			boundsA.TopLeft.y >= boundsB.BottomRight.y		  &&
			boundsB.TopRight.y >= boundsA.BottomLeft.y)
		{
			//spdlog::info(__FUNCTION__);

			return true;
		}

		return false;
	}


}