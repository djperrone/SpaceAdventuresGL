#include "sapch.h"

#include "ObjectManager.h"
#include "Novaura/Input/InputHandler.h"
//#include "MyObjects/ReloadIcon.h"
//#include "MyObjects/MouseCursor.h"
//#include "MyObjects/Player.h"
//#include "MyObjects/Asteroid.h"
//#include "MyObjects/Projectile.h"

namespace SpaceAdventures {



	//ObjectManager::ObjectManager(InputController* inputController)
	//	: isFirst(true)
	//{
	//	std::cout << "constructed objmanager!\n";
	//	
	//	m_MouseController = std::make_unique<MouseCursor>();
	//	m_ReloadIcon = std::make_unique<ReloadIcon>();
	//
	//	m_Player = std::make_shared<Player>(m_MouseController.get(), inputController);	
	//
	//	m_ObjectList.push_back(m_Player);
	//	m_ShipList.push_back(m_Player);
	//	
	//	m_CollisionManager = std::make_unique<CollisionManager>(&m_ObjectList, &m_AsteroidList);
	//	m_Spawner = std::make_unique<Spawner>(&m_ObjectList, &m_ShipList,&m_AsteroidList);
	//
	//	m_ProjectileManager = std::make_unique<ProjectileManager>();	
	//}

	ObjectManager::ObjectManager()
	{
		m_Spawner = std::make_unique<Spawner>(&m_AsteroidList, &m_ShipList);
		m_ProjectileManager = std::make_unique<ProjectileManager>();

		m_Player = std::make_shared<Player>();	
		m_ShipList.push_back(m_Player);
		m_CollisionManager = std::make_unique<CollisionManager>(&m_ShipList, &m_AsteroidList, &m_ProjectileList);


		//m_ProjectileList.emplace_back(std::make_unique<Projectile>(glm::vec2(0.0f, 0.0f), glm::vec2(0.05f, 0.5f), Team::Enemy,45.0f));
		//m_ProjectileList.emplace_back(std::make_unique<Projectile>(glm::vec2(0.5f,-0.5f), glm::vec2(0.05f, 0.5f), Team::Friend,0.0f));

	}



	void ObjectManager::Update(float dt)
	{
		
			m_Spawner->SpawnAsteroid();
			m_Spawner->SpawnUFO();


		//m_Spawner->SpawnAsteroid();

			for (auto& obj : m_AsteroidList)
			{
				obj->Update(dt);
			}
			for (auto& obj : m_ShipList)
			{
				//std::cout << "updating\n";
				obj->Update(dt);
			}

			for (auto& obj : m_ProjectileList)
			{
				//std::cout << "updating\n";
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

	/*bool ObjectManager::IsWithinBounds(Character* tempObject)
	{

	}*/

	/*Player* ObjectManager::GetPlayer()
	{
		return m_Player.get();
	}*/


}

