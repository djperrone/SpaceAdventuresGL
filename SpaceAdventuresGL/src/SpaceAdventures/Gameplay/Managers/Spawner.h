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

		template <typename T>
		void Spawn()
		{

			//T* temp1 = new T();


		/*	std::shared_ptr<T> temp = std::make_shared<T>();
			if (temp.get()->GetTag() == Tag::Ship)
			{
				m_ShipList->push_back((temp));

			}

			m_ObjList->push_back(std::move(temp));*/


		}

	private:
		//std::list <std::shared_ptr<Character>>* m_ObjList;
		std::list <std::shared_ptr<Ship>>* m_ShipList;
		std::list <std::unique_ptr<Asteroid>>* m_AsteroidList;
		//Dimensions m_Dimensions;
		


		time_t currentTime = 0;
		time_t previousTime = 0;

		time_t ufoCurrentTime = 0;
		time_t ufoPreviousTime = 0;
		double UFO_SPAWN_RATE = 5000;

		double ASTEROID_SPAWN_RATE = 1000;



		
	};
	

}

