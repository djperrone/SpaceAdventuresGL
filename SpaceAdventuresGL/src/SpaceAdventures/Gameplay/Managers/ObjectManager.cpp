#include "sapch.h"

#include "ObjectManager.h"
#include "Novaura/Input/InputHandler.h"

namespace SpaceAdventures {

	ObjectManager::ObjectManager()
	{
		m_Spawner = std::make_unique<Spawner>(&m_AsteroidList, &m_ShipList);
		m_ProjectileManager = std::make_unique<ProjectileManager>();

		m_Player = std::make_shared<Player>();	
		m_ShipList.push_back(m_Player);
		m_CollisionManager = std::make_unique<CollisionManager>(&m_ShipList, &m_AsteroidList, &m_ProjectileList);
	}

	void ObjectManager::Update(float dt)
	{		
			m_Spawner->SpawnAsteroid();
			m_Spawner->SpawnUFO();


			for (auto& obj : m_AsteroidList)
			{
				obj->Update(dt);
			}
			for (auto& obj : m_ShipList)
			{				
				obj->Update(dt);
			}

			for (auto& obj : m_ProjectileList)
			{				
				obj->Update(dt);
			}

			LoadAllProjectiles();
			m_CollisionManager->Tick();

			CleanList();
	}

	void ObjectManager::CleanList()
	{
		for (auto it = m_AsteroidList.begin(); it != m_AsteroidList.end(); )
		{
			if (!it->get()->IsAlive() || !IsWithinBounds(*it->get()))
			{
				it = m_AsteroidList.erase(it);
			}
			else
			{
				it++;
			}
		}

		for (auto it = m_ShipList.begin(); it != m_ShipList.end(); )
		{
			if (!it->get()->IsAlive() || !IsWithinBounds(*it->get()))
			{
				it = m_ShipList.erase(it);
			}
			else
			{
				it++;
			}
		}

		for (auto it = m_ProjectileList.begin(); it != m_ProjectileList.end(); )
		{
			if (!it->get()->IsAlive() || !IsWithinBounds(*it->get()))
			{
				it = m_ProjectileList.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void ObjectManager::LoadAllProjectiles()
	{
		m_ProjectileManager->LoadAllProjectiles(m_ShipList);
		auto list = m_ProjectileManager->GetProjectileList();
		std::copy(list.begin(), list.end(), std::back_inserter(m_ObjectList));
		std::copy(list.begin(), list.end(), std::back_inserter(m_ProjectileList));
		m_ProjectileManager->ClearProjectileList();
	}

	bool ObjectManager::IsWithinBounds(const Character& object)
	{
		Bounds bounds = object.GetBounds();
		if (bounds.TopLeft.y < -1.0f)
			return false;
		else
			return true;
	}
}

