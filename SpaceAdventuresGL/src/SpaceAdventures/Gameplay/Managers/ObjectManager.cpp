#include "sapch.h"

#include "ObjectManager.h"
#include "Novaura/Input/InputHandler.h"

namespace SpaceAdventures {

	ObjectManager::ObjectManager()
	{
		m_CharacterList.reserve(GameObjectData::MAX_CHARACTERS);
		m_ProjectileManager = std::make_unique<ProjectileManager>();

		m_Player = std::make_shared<Player>();	
		m_CharacterList.push_back(m_Player);
		m_Spawner = std::make_unique<Spawner>(m_CharacterList, m_Player);

		m_CollisionManager = std::make_unique<CollisionManager>(&m_CharacterList);
	}

	void ObjectManager::Update(float dt)
	{		
			m_Spawner->SpawnAsteroid();
			m_Spawner->SpawnUFO();

			int count = 0;

			for (auto& obj : m_CharacterList)
			{								
				if(obj->IsAlive())
					obj->Update(dt);
			}			

			LoadAllProjectiles();
			m_CollisionManager->Tick();

			CleanList();
	}

	void ObjectManager::CleanList()
	{
		for (auto object : m_CharacterList)
		{
			if (!IsWithinBounds(*object))
			{
				object->SetHealth(0);
			}
			if (!object->IsAlive())
			{
				object->SetIsCollidable(false);
			}
			
		}		
	}

	void ObjectManager::LoadAllProjectiles()
	{
		m_ProjectileManager->LoadAllProjectiles(m_Spawner->GetShipList());
		auto& list = m_ProjectileManager->GetProjectileList();
		if (list.size() > 0)
		{
			m_Spawner->SpawnProjectiles(list);
			m_ProjectileManager->ClearProjectileList();
		}		
	}

	bool ObjectManager::IsWithinBounds(const Character& object)
	{
		float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;
		Bounds bounds = object.GetBounds();
		if (bounds.TopLeft.y < -1.0f || bounds.BottomLeft.y > 1.2f || bounds.BottomLeft.x > aspectRatio || bounds.BottomRight.x < -aspectRatio)
			return false;
		else
			return true;
	}
}

