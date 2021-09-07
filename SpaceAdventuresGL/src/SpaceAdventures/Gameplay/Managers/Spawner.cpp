#include "sapch.h"

#include "Spawner.h"
#include "../GameObjects/Asteroid.h"
#include "../GameObjects/UFO.h"
#include "Novaura/Random.h"
#include "Novaura/Novaura.h"

namespace SpaceAdventures {


	Spawner::Spawner(std::list<std::unique_ptr<Asteroid>>* asteroidList, std::list<std::shared_ptr<Ship>>* shipList)
		:m_AsteroidList(asteroidList), m_ShipList(shipList)
	{
		time(&previousTime);
		time(&ufoPreviousTime);

		//gen(std::random_device());
	}

	void Spawner::SpawnAsteroid()
	{
		if (time(&currentTime) - previousTime >= 1)
		{			
			float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;

			m_AsteroidList->emplace_back(std::move(std::make_unique<Asteroid>(Novaura::Random::Float(-aspectRatio, aspectRatio), 1.0f)));
			//std::cout << "asteorielist size " << m_AsteroidList->size() << std::endl;
			previousTime = currentTime;
			

		}
	}

	void Spawner::SpawnAsteroid(float x, float y)
	{
		if (time(&currentTime) - previousTime >= 1)
		{

			m_AsteroidList->emplace_back(std::move(std::make_unique<Asteroid>(x, y)));
			previousTime = currentTime;
		}
	}

	void Spawner::SpawnUFO()
	{

		time(&ufoCurrentTime);
		if (ufoCurrentTime - ufoPreviousTime >= 5 && m_ShipList->size() < 3)		
		{
			float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;

			//std::cout << "shiplist  size " << m_ShipList->size() << std::endl;

			std::shared_ptr<UFO> tempUFO = std::make_shared<UFO>(Novaura::Random::Float(-aspectRatio, aspectRatio), 0.7f);
			
			//m_ObjList->push_back(tempUFO);
			m_ShipList->push_back(std::move(tempUFO));
			ufoPreviousTime = ufoCurrentTime;
		}
		
	}

	void Spawner::SpawnUFO(float x, float y)
	{
		/*if (m_ShipList->size() < 3)
		{
			std::shared_ptr<UFO> tempUFO = std::make_shared<UFO>(x, y);
			m_ObjList->push_back(tempUFO);
			m_ShipList->push_back(std::move(tempUFO));
			ufoPreviousTime = ufoCurrentTime;
		}*/
	}

}