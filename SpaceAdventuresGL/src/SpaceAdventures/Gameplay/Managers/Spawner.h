#pragma once
#include "GameObjectData.h"
#include <random>

#include "SpaceAdventures/Gameplay/GameObjects/Asteroid.h"
#include "SpaceAdventures/Gameplay/GameObjects/SpaceShip.h"
#include "SpaceAdventures/Gameplay/GameObjects/Projectile.h"
#include "../GameObjects/Player.h"

namespace SpaceAdventures {
	
	//class Character;

	class Spawner
	{
	public:
		//Spawner(std::list<std::unique_ptr<Asteroid>>* asteroidList, std::list<std::shared_ptr<Ship>>* shipList);
		Spawner(std::vector<std::shared_ptr<Character>>& characterList, std::shared_ptr<Player> player);

		void SpawnAsteroid();		
		void SpawnUFO();		
		void SpawnProjectiles(std::vector<std::shared_ptr<Projectile>>&);
		
		//std::list <std::shared_ptr<Ship>>* m_ShipList;
		//std::list <std::unique_ptr<Asteroid>>* m_AsteroidList;	

		inline const std::vector<std::shared_ptr<Ship>>& GetShipList() const { return m_ShipList; }
		inline std::vector<std::shared_ptr<Ship>>& GetShipList() { return m_ShipList; }


	private:
		std::vector<std::shared_ptr<Ship>> m_ShipList;
		std::vector<std::shared_ptr<Asteroid>> m_AsteroidList;
		std::vector<std::shared_ptr<Projectile>> m_ProjectileList;

		time_t currentTime = 0;
		time_t previousTime = 0;

		time_t ufoCurrentTime = 0;
		time_t ufoPreviousTime = 0;
		double UFO_SPAWN_RATE = 5000;

		double ASTEROID_SPAWN_RATE = 1000;

		uint32_t m_CurrentShipSlot = 1;
		uint32_t m_CurrentAsteroidSlot = 0;
		uint32_t m_CurrentProjectileSlot = 0;	
		
	};

}

