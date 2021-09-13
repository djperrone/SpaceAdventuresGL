#include "sapch.h"

#include "Spawner.h"
#include "../GameObjects/Asteroid.h"
#include "../GameObjects/UFO.h"
#include "SpaceAdventures/Actors/Character.h"
#include "Novaura/Random.h"
#include "Novaura/Novaura.h"
#include "ObjectManager.h"


namespace SpaceAdventures {


	Spawner::Spawner(std::vector<std::shared_ptr<Character>>& characterList, std::shared_ptr<Player> player)		
	{		
		m_ShipList.reserve(GameObjectData::MAX_SHIPS);
		m_AsteroidList.reserve(GameObjectData::MAX_ASTEROIDS);
		m_ProjectileList.reserve(GameObjectData::MAX_PROJECTILES);

		m_ShipList.push_back(player);

		for (uint32_t i = 0; i < GameObjectData::MAX_PROJECTILES; i++)
		{
			auto projectile = std::make_shared<Projectile>();
			projectile->SetHealth(0);

			m_ProjectileList.push_back(projectile);
			characterList.push_back(projectile);
			//characterList[i + GameObjectData::MAX_SHIPS + GameObjectData::MAX_PROJECTILES] = projectile;
		}

		for (uint32_t i = 1; i < GameObjectData::MAX_SHIPS; i++)
		{			
			auto ufo = std::make_shared<UFO>();
			ufo->SetHealth(0);
			m_ShipList.push_back(ufo);
			characterList.push_back(ufo);
			//characterList[i] = ufo;
		}


		for (uint32_t i = 0; i < GameObjectData::MAX_ASTEROIDS; i++)
		{
			auto asteroid = std::make_shared<Asteroid>();
			asteroid->SetHealth(0);
			m_AsteroidList.push_back(asteroid);
			characterList.push_back(asteroid);
		}	
		

		time(&previousTime);
		time(&ufoPreviousTime);

		//gen(std::random_device());
	}

	void Spawner::SpawnAsteroid()
	{
		if (time(&currentTime) - previousTime >= 1)
		{			
			float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;

			uint32_t count = 0;
			while (m_AsteroidList[m_CurrentAsteroidSlot]->IsAlive())
			{
				m_CurrentAsteroidSlot = (m_CurrentAsteroidSlot + 1) % GameObjectData::MAX_ASTEROIDS;
				
				if (count++ >= GameObjectData::MAX_ASTEROIDS)
				{
					spdlog::error("NOT ENOUGH ROOM TO SPAWN ASTEROID");
					return;
				}
			}

			auto currentAsteroid = m_AsteroidList[m_CurrentAsteroidSlot];

			float x;
			if (aspectRatio == 0)
			{
				x = Novaura::Random::Float(-1.0, 1.0);
			}
			else
			{
				x = Novaura::Random::Float(-aspectRatio - (aspectRatio * 0.25), aspectRatio + aspectRatio * 0.25);
				if (x < -aspectRatio)
				{
					currentAsteroid->SetVelocity(glm::vec2(Novaura::Random::Float(0.1,0.5f), 1.0f));
				}
				else if (x > aspectRatio)
				{
					currentAsteroid->SetVelocity(glm::vec2(Novaura::Random::Float(0.1, 0.5f) * -1.0f, 1.0f));
				}
				else if (x < 0.0f)
				{
					currentAsteroid->SetVelocity(glm::vec2(Novaura::Random::Float(0.1, 0.25f), 1.0f));
				}
				else if (x > 0.0f)
				{
					currentAsteroid->SetVelocity(glm::vec2(Novaura::Random::Float(0.1, 0.25f) * -1.0f, 1.0f));
				}
			}
			currentAsteroid->SetHealth(currentAsteroid->GetMaxHealth());
			currentAsteroid->SetIsCollidable(true);
			currentAsteroid->SetPosition(x, 1.0f);			
			previousTime = currentTime;
		}
	}	

	void Spawner::SpawnUFO()
	{
		time(&ufoCurrentTime);
		if (ufoCurrentTime - ufoPreviousTime >= 5)		
		{
			float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;			

			for (auto& ship : m_ShipList)
			{
				if (!ship->IsAlive())
				{					
					ship->SetHealth(ship->GetMaxHealth());
					ship->SetIsCollidable(true);

					ship->SetPosition(Novaura::Random::Float(-aspectRatio, aspectRatio), 0.7f);
					break;
				}
			}			
			
			ufoPreviousTime = ufoCurrentTime;
		}		
	}

	void Spawner::SpawnProjectiles(std::vector<std::shared_ptr<Projectile>>& projectileList)
	{	
		int indexSave = 0;

		for (auto oProjectile : projectileList)
		{
			for (indexSave; indexSave < m_ProjectileList.size(); indexSave++)
			{
				if (!m_ProjectileList[indexSave]->IsAlive())
				{				
					m_ProjectileList[indexSave]->Reset(*oProjectile);
					break;					

				}
				
			}
		}		
	}
}