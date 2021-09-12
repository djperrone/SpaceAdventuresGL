#pragma once
#include <random>

namespace SpaceAdventures {


	class Asteroid;
	class Ship;

	class Spawner
	{
	public:
		Spawner(std::list<std::unique_ptr<Asteroid>>* asteroidList, std::list<std::shared_ptr<Ship>>* shipList);

		void SpawnAsteroid();
		void SpawnAsteroid(float x, float y);
		void SpawnUFO();
		void SpawnUFO(float x, float y);		

	private:
		
		std::list <std::shared_ptr<Ship>>* m_ShipList;
		std::list <std::unique_ptr<Asteroid>>* m_AsteroidList;	

		time_t currentTime = 0;
		time_t previousTime = 0;

		time_t ufoCurrentTime = 0;
		time_t ufoPreviousTime = 0;
		double UFO_SPAWN_RATE = 5000;

		double ASTEROID_SPAWN_RATE = 1000;
		
	};

}

